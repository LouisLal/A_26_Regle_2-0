/*
 * angle.h
 *
 * Calcul d'angle en entiers (sans virgule flottante), en centièmes de degré.
 */
#ifndef ANGLE_H
#define ANGLE_H

#include <stdint.h>

#define CDEG_90    9000
#define CDEG_180  18000
#define CDEG_360  36000

/* Équivalent de atan2(y, x) en centièmes de degré, dans (-18000, 18000].
 * LUT de 17 points sur [0, 45°] + interpolation linéaire.
 * Erreur max ~0.04° (mesurée sur 200 000 points). |x| et |y| < 2^19. */
int16_t ANGLE_Atan2(int32_t y, int32_t x);

/* Ramène un angle (centièmes de degré) dans (-18000, 18000]. */
int16_t ANGLE_Ramene180(int32_t a);

#endif /* ANGLE_H */
