# 1 "app/angle.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/opt/microchip/xc8/v3.10/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "app/angle.c" 2
# 14 "app/angle.c"
# 1 "app/angle.h" 1








# 1 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 1 3



# 1 "/opt/microchip/xc8/v3.10/pic/include/c99/musl_xc8.h" 1 3
# 5 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3
# 26 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 3
# 1 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 1 3
# 133 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef short intptr_t;
# 164 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 3
# 1 "/opt/microchip/xc8/v3.10/pic/include/c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "/opt/microchip/xc8/v3.10/pic/include/c99/stdint.h" 2 3
# 10 "app/angle.h" 2








int16_t ANGLE_Atan2(int32_t y, int32_t x);


int16_t ANGLE_Ramene180(int32_t a);
# 15 "app/angle.c" 2






static const uint16_t lut_atan[16 + 1] = {
       0, 358, 713, 1062, 1404, 1735, 2056, 2363, 2657,
    2936, 3201, 3451, 3687, 3909, 4119, 4315, 4500
};


static uint16_t atan_octant(uint32_t n, uint32_t d)
{
    uint16_t q = (uint16_t)((n << 12) / d);
    uint8_t i;
    uint16_t f;
    uint16_t a0;

    if (q >= (1u << 12)) {
        return lut_atan[16];
    }
    i = (uint8_t)(q >> (12 - 4));
    f = q & ((1u << (12 - 4)) - 1u);
    a0 = lut_atan[i];

    return (uint16_t)(a0 + (uint16_t)(((uint32_t)(lut_atan[i + 1u] - a0) * f
                                       + (1u << ((12 - 4) - 1))) >> (12 - 4)));
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
        a = (int16_t)(9000 - (int16_t)atan_octant(ax, ay));
    }
    if (x < 0) {
        a = (int16_t)(18000 - a);
    }
    if (y < 0) {
        a = (int16_t)-a;
    }
    return a;
}

int16_t ANGLE_Ramene180(int32_t a)
{
    while (a > 18000) a -= 36000;
    while (a <= -18000) a += 36000;
    return (int16_t)a;
}
