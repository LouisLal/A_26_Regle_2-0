/*
 * lis2hh12.c
 *
 * Utilise le driver I2C hôte généré par MCC (mssp1.c), qui fonctionne par
 * interruptions : les interruptions globales et périphériques doivent être
 * activées avant d'appeler ces fonctions.
 */
#include "lis2hh12.h"
#include "../mcc_generated_files/system/system.h"

/* Délai max pour une transaction (pas de 100 us). 62.5 kHz => ~1.5 ms pour
 * 7 octets, donc 20 ms laisse beaucoup de marge. */
#define I2C_TIMEOUT_STEPS 200

static bool i2c_wait(void)
{
    uint16_t n = I2C_TIMEOUT_STEPS;
    while (I2C1_IsBusy()) {
        if (n-- == 0) {
            return false;
        }
        __delay_us(100);
    }
    return I2C1_ErrorGet() == I2C_ERROR_NONE;
}

static bool write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val;
    if (!I2C1_Write(LIS2HH12_ADDR, buf, 2)) {
        return false;
    }
    return i2c_wait();
}

static bool read_regs(uint8_t reg, uint8_t *data, uint8_t len)
{
    if (!I2C1_WriteRead(LIS2HH12_ADDR, &reg, 1, data, len)) {
        return false;
    }
    return i2c_wait();
}

bool LIS2HH12_Init(void)
{
    uint8_t id = 0;

    if (!read_regs(LIS2HH12_REG_WHO_AM_I, &id, 1) || id != LIS2HH12_WHO_AM_I_ID) {
        return false;
    }

    /* CTRL4 : BW auto, FS = ±2 g, IF_ADD_INC = 1 (auto-incrément pour lire
     * X/Y/Z d'un coup), I2C actif. */
    if (!write_reg(LIS2HH12_REG_CTRL4, 0x04)) {
        return false;
    }

    /* CTRL1 : HR = 1, ODR = 50 Hz (010), BDU = 1, Z/Y/X activés. */
    return write_reg(LIS2HH12_REG_CTRL1, 0xAF);
}

bool LIS2HH12_PowerDown(void)
{
    /* CTRL1 : ODR = 000 (power-down), le reste inchangé. */
    return write_reg(LIS2HH12_REG_CTRL1, 0x8F);
}

bool LIS2HH12_Read(lis2hh12_data_t *out)
{
    uint8_t raw[6];

    if (!read_regs(LIS2HH12_REG_OUT_X_L, raw, 6)) {
        return false;
    }
    out->x = (int16_t)((uint16_t)raw[1] << 8 | raw[0]);
    out->y = (int16_t)((uint16_t)raw[3] << 8 | raw[2]);
    out->z = (int16_t)((uint16_t)raw[5] << 8 | raw[4]);
    return true;
}
