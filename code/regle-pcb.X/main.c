/*
 * main.c - Rapporteur d'angle numérique (C3I A26 - Règle PCB)
 *
 * Matériel : PIC16LF19156 @ 1 MHz, accéléromètre LIS2HH12 (I2C), LCD Lumex
 * LCD-S401M16KR (4 x 7 segments), 5 DEL en charlieplexing, bouton S1 sur RA5.
 *
 * Fonctionnement :
 *   - La règle posée sur sa tranche mesure l'angle de son grand axe par
 *     rapport à l'horizontale (gravité dans le plan du PCB, axes X/Y).
 *   - Le LCD affiche l'angle au degré près (-180 à 180).
 *   - Les DEL font un niveau à bulle : D3 (centre) = à 0/90/180 degrés près.
 *   - Appui court sur S1   : remise à zéro (mesure relative).
 *   - Appui long (> 1.5 s) : retour à la mesure absolue (affiche "AbS").
 *   - Règle posée à plat : "FLAt" (l'angle dans le plan n'a plus de sens).
 *   - Capteur absent : "Err" et nouvelle tentative chaque seconde.
 *   - JP1 soudé : économie d'énergie. Après ~1 min sans appui sur S1, tout
 *     s'éteint (LCD, DEL, accéléromètre, PIC en SLEEP). Un appui sur S1
 *     rallume la règle sans changer le zéro ; cet appui n'est pas compté
 *     comme une remise à zéro.
 */
#include "mcc_generated_files/system/system.h"
#include "app/lis2hh12.h"
#include "app/afficheur.h"
#include "app/del.h"
#include "app/angle.h"
#include "app/veille.h"

/* --- Calibration de l'orientation -------------------------------------------
 * À la première mise sous tension, poser la règle sur sa tranche sur une
 * surface de niveau (mode absolu). L'écran doit afficher ~0.0.
 *   - Affiche ~90, -90 ou 180 : ajuster ANGLE_DECALAGE_CDEG (-9000, 9000,
 *     18000 ; en centièmes de degré).
 *   - L'angle augmente dans le mauvais sens : mettre ANGLE_SENS à -1.
 */
#define ANGLE_DECALAGE_CDEG 0
#define ANGLE_SENS          1

/* --- Paramètres ------------------------------------------------------------ */
#define PERIODE_MS          50u     /* boucle principale à 20 Hz */
#define AFF_DIVISEUR        4u      /* LCD rafraîchi toutes les 200 ms */
#define FILTRE_DIV          4       /* filtre passe-bas : alpha = 1/4 */
#define FILTRE_ECHELLE      8       /* état du filtre = accél. x 8 (précision) */
#define APPUI_LONG_TICKS    30u     /* 30 x 50 ms = 1.5 s */
#define NIVEAU_FIN_CDEG     50      /* |écart| <= 0.5 deg -> D3 */
#define NIVEAU_MOYEN_CDEG   300     /* |écart| <= 3 deg   -> D2 / D4 */
#define VEILLE_TICKS        1200u   /* 1200 x 50 ms = ~1 min sans appui */

#define BOUTON_APPUYE()     (PORTAbits.RA5 == 0)    /* S1 vers GND */

/* Choisit la DEL du niveau à bulle selon l'écart au multiple de 90 le plus
 * proche (fonctionne règle à l'horizontale comme à la verticale). */
static uint8_t del_niveau(int16_t angle)
{
    /* écart dans (-45°, 45°] par rapport au multiple de 90° le plus proche */
    int16_t ecart = angle % CDEG_90;
    if (ecart > CDEG_90 / 2)   ecart -= CDEG_90;
    if (ecart <= -CDEG_90 / 2) ecart += CDEG_90;

    if (ecart > NIVEAU_MOYEN_CDEG)   return 5;
    if (ecart > NIVEAU_FIN_CDEG)     return 4;
    if (ecart >= -NIVEAU_FIN_CDEG)   return 3;
    if (ecart >= -NIVEAU_MOYEN_CDEG) return 2;
    return 1;
}

int main(void)
{
    lis2hh12_data_t acc;
    int32_t fx = 0, fy = 0, fz = 0;     /* accélération filtrée x 8 */
    bool filtre_pret = false;
    bool capteur_ok = false;
    int16_t zero = 0;                   /* centièmes de degré */
    uint8_t tick_aff = 0;
    uint8_t tick_bouton = 0;
    uint8_t tick_reessai = 0;
    uint8_t tick_message = 0;   /* > 0 : un message est affiché, on attend */
    uint16_t tick_inactif = 0;  /* temps depuis le dernier appui sur S1 */
    bool ignore_bouton = false; /* appui de réveil : ignoré jusqu'au relâchement */

    SYSTEM_Initialize();

    /* Bouton S1 sur RA5 : pas de pull-up externe, on active la pull-up interne */
    WPUAbits.WPUA5 = 1;

    DEL_Init();
    VEILLE_Init();

    /* Le driver I2C de MCC fonctionne par interruptions */
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    AFF_Texte("8888", 0x0F);    /* test de tous les segments */
    for (uint8_t i = 1; i <= 5u; i++) {
        DEL_Allume(i);
        __delay_ms(150);
    }
    DEL_Allume(0);

    __delay_ms(20);             /* démarrage du LIS2HH12 (boot ~10 ms) */
    capteur_ok = LIS2HH12_Init();

    while (1)
    {
        __delay_ms(PERIODE_MS);

        /* ---- Économie d'énergie (JP1 soudé) ---- */
        if (BOUTON_APPUYE() || !VEILLE_Activee()) {
            tick_inactif = 0;
        } else if (++tick_inactif >= VEILLE_TICKS) {
            capteur_ok = VEILLE_Dormir();   /* revient au réveil (S1 appuyé) */
            tick_inactif = 0;
            filtre_pret = false;
            ignore_bouton = true;
            tick_bouton = 0;
            tick_message = 0;
            tick_reessai = 0;
            tick_aff = AFF_DIVISEUR;        /* réaffiche l'angle tout de suite */
            continue;
        }

        /* ---- Capteur absent : on réessaie chaque seconde ---- */
        if (!capteur_ok) {
            AFF_Texte("Err ", 0);
            DEL_Allume(0);
            if (++tick_reessai >= 20u) {
                tick_reessai = 0;
                capteur_ok = LIS2HH12_Init();
                filtre_pret = false;
            }
            continue;
        }

        if (!LIS2HH12_Read(&acc)) {
            capteur_ok = false;
            continue;
        }

        /* ---- Filtre passe-bas ---- */
        if (!filtre_pret) {
            fx = (int32_t)acc.x * FILTRE_ECHELLE;
            fy = (int32_t)acc.y * FILTRE_ECHELLE;
            fz = (int32_t)acc.z * FILTRE_ECHELLE;
            filtre_pret = true;
        } else {
            fx += ((int32_t)acc.x * FILTRE_ECHELLE - fx) / FILTRE_DIV;
            fy += ((int32_t)acc.y * FILTRE_ECHELLE - fy) / FILTRE_DIV;
            fz += ((int32_t)acc.z * FILTRE_ECHELLE - fz) / FILTRE_DIV;
        }

        /* ---- À plat ? (< 0.5 g dans le plan du PCB) ----
         * plan² < total² / 4  <=>  3 (x² + y²) < z²
         * Calculé sur 12 bits (>> 7 depuis l'état x 8) pour rester en 32 bits. */
        int16_t px = (int16_t)(fx >> 7), py = (int16_t)(fy >> 7), pz = (int16_t)(fz >> 7);
        uint32_t plan2 = (uint32_t)((int32_t)px * px + (int32_t)py * py);
        bool a_plat = 3u * plan2 < (uint32_t)((int32_t)pz * pz);

        /* ---- Angle dans le plan du PCB (centièmes de degré) ---- */
        int16_t absolu = ANGLE_Ramene180((int32_t)ANGLE_SENS * ANGLE_Atan2(fx, fy)
                                         + ANGLE_DECALAGE_CDEG);
        int16_t angle = ANGLE_Ramene180((int32_t)absolu - zero);

        /* ---- Bouton : court = zéro, long = absolu ---- */
        if (ignore_bouton) {
            if (!BOUTON_APPUYE()) {
                ignore_bouton = false;      /* appui de réveil terminé */
            }
        } else if (BOUTON_APPUYE()) {
            if (tick_bouton < 255u) tick_bouton++;
            if (tick_bouton == APPUI_LONG_TICKS) {
                zero = 0;
                AFF_Texte("AbS ", 0);
                tick_message = 20u;     /* 1 s */
            }
        } else {
            if (tick_bouton >= 1u && tick_bouton < APPUI_LONG_TICKS && !a_plat) {
                zero = absolu;
                angle = 0;
                tick_aff = AFF_DIVISEUR;    /* affiche 0 tout de suite */
            }
            tick_bouton = 0;
        }

        /* ---- Sorties ---- */
        if (a_plat) {
            DEL_Allume(0);
        } else {
            DEL_Allume(del_niveau(angle));
        }

        if (tick_message > 0u) {
            tick_message--;
            continue;
        }
        if (++tick_aff >= AFF_DIVISEUR) {
            tick_aff = 0;
            if (a_plat) {
                AFF_Texte("FLAt", 0);
            } else {
                AFF_Angle(angle);
            }
        }
    }
}
