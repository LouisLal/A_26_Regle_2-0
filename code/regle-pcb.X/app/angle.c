/*
 * angle.c
 *
 * atan2 par table :
 *   1. on se ramène au premier octant (0..45°) : r = min(|x|,|y|) / max(...)
 *   2. r est calculé en Q12 (0..4096), puis découpé en index (4 bits) et
 *      fraction (8 bits) pour interpoler entre deux points de la table ;
 *   3. on reconstruit le quadrant par symétrie.
 *
 * 17 points suffisent pour un affichage au degré : erreur max ~0.04°, ce qui
 * garde aussi le seuil de 0.5° du niveau à DEL fiable. (9 points : ~0.09°,
 * 5 points : ~0.3°. Plus de 33 points n'apporte plus rien.)
 */
#include "angle.h"

#define LUT_N      16                   /* intervalles sur [0, 45°] */
#define LUT_Q      12                   /* ratio en Q12 */
#define LUT_FRAC   (LUT_Q - 4)          /* 8 bits de fraction (16 = 2^4) */

/* atan(i / 16) en centièmes de degré, i = 0..16 */
static const uint16_t lut_atan[LUT_N + 1] = {
       0,  358,  713, 1062, 1404, 1735, 2056, 2363, 2657,
    2936, 3201, 3451, 3687, 3909, 4119, 4315, 4500
};

/* atan(n / d) pour 0 <= n <= d, d > 0 */
static uint16_t atan_octant(uint32_t n, uint32_t d)
{
    uint16_t q = (uint16_t)((n << LUT_Q) / d);      /* 0..4096 */
    uint8_t i;
    uint16_t f;
    uint16_t a0;

    if (q >= (1u << LUT_Q)) {
        return lut_atan[LUT_N];
    }
    i = (uint8_t)(q >> LUT_FRAC);
    f = q & ((1u << LUT_FRAC) - 1u);
    a0 = lut_atan[i];
    /* écart max entre 2 points = 358, x 255 : dépasse 16 bits -> calcul 32 bits */
    return (uint16_t)(a0 + (uint16_t)(((uint32_t)(lut_atan[i + 1u] - a0) * f
                                       + (1u << (LUT_FRAC - 1))) >> LUT_FRAC));
}

int16_t ANGLE_Atan2(int32_t y, int32_t x)
{
    uint32_t ax = (uint32_t)(x < 0 ? -x : x);
    uint32_t ay = (uint32_t)(y < 0 ? -y : y);
    int16_t a;

    if (ax == 0u && ay == 0u) {
        return 0;
    }
    if (ay <= ax) {
        a = (int16_t)atan_octant(ay, ax);
    } else {
        a = (int16_t)(CDEG_90 - (int16_t)atan_octant(ax, ay));
    }
    if (x < 0) {
        a = (int16_t)(CDEG_180 - a);
    }
    if (y < 0) {
        a = (int16_t)-a;
    }
    return a;
}

int16_t ANGLE_Ramene180(int32_t a)
{
    while (a > CDEG_180)   a -= CDEG_360;
    while (a <= -CDEG_180) a += CDEG_360;
    return (int16_t)a;
}
