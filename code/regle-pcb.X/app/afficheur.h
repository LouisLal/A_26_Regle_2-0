/*
 * afficheur.h
 *
 * Affichage sur le LCD Lumex LCD-S401M16KR (4 chiffres 7 segments,
 * 1/4 duty, 1/3 bias) piloté par le module LCD du PIC16LF19156.
 */
#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <stdint.h>
#include <stdbool.h>

/* Affiche 4 caractères (chiffres, ' ', '-', et quelques lettres :
 * A b C d E F L r S t). dp_mask : bit0 = DP1, bit1 = DP2, bit2 = DP3,
 * bit3 = deux-points (COL). */
void AFF_Texte(const char txt[4], uint8_t dp_mask);

/* Affiche un angle donné en centièmes de degré (ex. -4530 = -45.30°),
 * arrondi au degré et aligné à droite : "   5", " -45", "-180". */
void AFF_Angle(int16_t cdeg);

/* Efface l'écran. */
void AFF_Efface(void);

#endif /* AFFICHEUR_H */
