/*
 * veille.h
 *
 * Option d'économie d'énergie sélectionnée par le cavalier JP1 (RA7) :
 *   - JP1 ouvert (RA7 tiré à 3V par la pull-up interne) : toujours allumé.
 *   - JP1 soudé  (RA7 à GND) : après 1 minute sans appui sur S1, l'écran,
 *     les DEL et l'accéléromètre s'éteignent et le PIC passe en SLEEP.
 *     Un appui sur S1 réveille la règle ; le zéro (mode relatif) est conservé.
 */
#ifndef VEILLE_H
#define VEILLE_H

#include <stdbool.h>

void VEILLE_Init(void);

/* true si le cavalier JP1 est soudé (option économie d'énergie active). */
bool VEILLE_Activee(void);

/* Éteint tout et dort jusqu'à un appui sur S1 (front descendant sur RA5).
 * Au retour, le LCD est réactivé ; l'accéléromètre est réinitialisé et le
 * résultat de LIS2HH12_Init() est retourné. */
bool VEILLE_Dormir(void);

#endif /* VEILLE_H */
