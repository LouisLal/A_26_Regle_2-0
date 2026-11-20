/*
 * afficheur.c
 *
 * Correspondance (datasheet Lumex + routage du PCB) :
 *
 *   Broche LCD | Réseau  | PIC        | COM0 | COM1 | COM2 | COM3
 *   -----------+---------+------------+------+------+------+------
 *        1     | LCD_C0  | RB4 COM0   |      |      |      |
 *        2     | LCD_C1  | RB5 COM1   |      |      |      |
 *        3     | LCD_C2  | RC2 COM2   |      |      |      |
 *        4     | LCD_C3  | RA4 COM3   |      |      |      |
 *        5     | LCD_S0  | RA0 SEG0   |  1D  |  1E  |  1G  |  1F
 *        6     | LCD_S1  | RA1 SEG1   |  DP1 |  1C  |  1B  |  1A
 *        7     | LCD_S2  | RA2 SEG2   |  2D  |  2E  |  2G  |  2F
 *        8     | LCD_S3  | RA3 SEG3   |  DP2 |  2C  |  2B  |  2A
 *        9     | LCD_S4  | RB0 SEG8   |  3D  |  3E  |  3G  |  3F
 *       10     | LCD_S5  | RB1 SEG9   |  DP3 |  3C  |  3B  |  3A
 *       11     | LCD_S6  | RB2 SEG10  |  4D  |  4E  |  4G  |  4F
 *       12     | LCD_S7  | RB3 SEG11  |  COL |  4C  |  4B  |  4A
 *
 * Chaque chiffre n utilise donc deux SEG consécutifs :
 *   - SEG pair   : D, E, G, F sur COM0..COM3
 *   - SEG impair : DP/COL, C, B, A sur COM0..COM3
 * Les chiffres 1-2 sont dans LCDDATA0/6/12/18 (SEG0-7) et les chiffres 3-4
 * dans LCDDATA1/7/13/19 (SEG8-15), aux bits 0-1 (chiffre impair) ou 2-3.
 */
#include "afficheur.h"
#include <xc.h>

/* Bits de segments dans la police */
#define SA 0x01
#define SB 0x02
#define SC 0x04
#define SD 0x08
#define SE 0x10
#define SF 0x20
#define SG 0x40

static const uint8_t chiffres[10] = {
    SA|SB|SC|SD|SE|SF,      /* 0 */
    SB|SC,                  /* 1 */
    SA|SB|SD|SE|SG,         /* 2 */
    SA|SB|SC|SD|SG,         /* 3 */
    SB|SC|SF|SG,            /* 4 */
    SA|SC|SD|SF|SG,         /* 5 */
    SA|SC|SD|SE|SF|SG,      /* 6 */
    SA|SB|SC,               /* 7 */
    SA|SB|SC|SD|SE|SF|SG,   /* 8 */
    SA|SB|SC|SD|SF|SG,      /* 9 */
};

static uint8_t police(char c)
{
    if (c >= '0' && c <= '9') {
        return chiffres[c - '0'];
    }
    switch (c) {
        case '-': return SG;
        case 'A': return SA|SB|SC|SE|SF|SG;
        case 'b': return SC|SD|SE|SF|SG;
        case 'C': return SA|SD|SE|SF;
        case 'd': return SB|SC|SD|SE|SG;
        case 'E': return SA|SD|SE|SF|SG;
        case 'F': return SA|SE|SF|SG;
        case 'L': return SD|SE|SF;
        case 'r': return SE|SG;
        case 'S': return SA|SC|SD|SF|SG;
        case 't': return SD|SE|SF|SG;
        default:  return 0;     /* espace / inconnu */
    }
}

/* Écrit un registre LCDDATA seulement quand le module le permet (WA = 1),
 * sinon WERR est levé et l'écriture est ignorée. */
#define LCD_ECRIT(reg, val) do { while (!LCDPSbits.WA) {} (reg) = (val); } while (0)

void AFF_Texte(const char txt[4], uint8_t dp_mask)
{
    /* com[c][b] : c = COM0..3, b = 0 -> SEG0-7, 1 -> SEG8-15 */
    uint8_t com[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

    for (uint8_t n = 0; n < 4; n++) {
        uint8_t s = police(txt[n]);
        uint8_t b = n >> 1;                         /* banque */
        uint8_t pair = (uint8_t)(1u << ((n & 1u) * 2u));
        uint8_t impair = (uint8_t)(pair << 1);

        if (s & SD) com[0][b] |= pair;
        if (s & SE) com[1][b] |= pair;
        if (s & SG) com[2][b] |= pair;
        if (s & SF) com[3][b] |= pair;

        if (dp_mask & (1u << n)) com[0][b] |= impair;   /* DP1..3 / COL */
        if (s & SC) com[1][b] |= impair;
        if (s & SB) com[2][b] |= impair;
        if (s & SA) com[3][b] |= impair;
    }

    LCD_ECRIT(LCDDATA0,  com[0][0]);
    LCD_ECRIT(LCDDATA1,  com[0][1]);
    LCD_ECRIT(LCDDATA6,  com[1][0]);
    LCD_ECRIT(LCDDATA7,  com[1][1]);
    LCD_ECRIT(LCDDATA12, com[2][0]);
    LCD_ECRIT(LCDDATA13, com[2][1]);
    LCD_ECRIT(LCDDATA18, com[3][0]);
    LCD_ECRIT(LCDDATA19, com[3][1]);
}

void AFF_Efface(void)
{
    AFF_Texte("    ", 0);
}

void AFF_Angle(int16_t cdeg)
{
    char t[4] = {' ', ' ', ' ', ' '};
    bool neg = cdeg < 0;
    uint16_t a = (uint16_t)(neg ? -cdeg : cdeg);
    uint16_t deg = (uint16_t)((a + 50u) / 100u);    /* arrondi au degré */
    uint8_t i = 3;                                  /* premier chiffre utilisé */

    /* Aligné à droite : "   5", " -45", " 180", "-180" */
    t[3] = (char)('0' + deg % 10u);
    if (deg >= 10u) {
        t[2] = (char)('0' + (deg / 10u) % 10u);
        i = 2;
    }
    if (deg >= 100u) {
        t[1] = (char)('0' + deg / 100u);
        i = 1;
    }
    if (neg && deg != 0u) {
        t[i - 1] = '-';     /* signe collé au premier chiffre */
    }
    AFF_Texte(t, 0);
}
