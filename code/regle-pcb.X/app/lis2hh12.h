/*
 * lis2hh12.h
 *
 * Driver minimal pour l'accéléromètre LIS2HH12 (ST) sur I2C1 (MSSP1).
 *
 * Câblage sur la règle :
 *   - SCL -> RC3 (accel_clock), SDA -> RC4 (accel_data), pull-ups 4.7k
 *   - CS  -> 3V  => mode I2C
 *   - SDO/SA0 -> GND => adresse 7 bits 0x1E
 */
#ifndef LIS2HH12_H
#define LIS2HH12_H

#include <stdint.h>
#include <stdbool.h>

#define LIS2HH12_ADDR        0x1E   /* SA0 = 0 */
#define LIS2HH12_WHO_AM_I_ID 0x41

/* Registres utilisés */
#define LIS2HH12_REG_WHO_AM_I 0x0F
#define LIS2HH12_REG_CTRL1    0x20
#define LIS2HH12_REG_CTRL4    0x23
#define LIS2HH12_REG_STATUS   0x27
#define LIS2HH12_REG_OUT_X_L  0x28

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} lis2hh12_data_t;

/* Vérifie WHO_AM_I puis configure : 50 Hz, haute résolution, BDU, ±2 g.
 * Retourne false si le capteur ne répond pas ou si l'ID est mauvais. */
bool LIS2HH12_Init(void);

/* Met le capteur en power-down (ODR = 000, ~5 uA -> quelques nA).
 * LIS2HH12_Init() le réveille. */
bool LIS2HH12_PowerDown(void);

/* Lit X, Y, Z (valeurs brutes, ±2 g => ~16393 LSB/g).
 * Retourne false en cas d'erreur I2C. */
bool LIS2HH12_Read(lis2hh12_data_t *out);

#endif /* LIS2HH12_H */
