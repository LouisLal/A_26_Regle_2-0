/*
 * del.c
 *
 * Connexions des DEL (pastille 1 -> pastille 2), tirées du PCB :
 *   D1 : N1 -> N2     D2 : N2 -> N1     D3 : N3 -> N2
 *   D4 : N3 -> N1     D5 : N1 -> N3
 */
#include "del.h"
#include <xc.h>

#define N1 1
#define N2 2
#define N3 3

static const uint8_t del_p1[5] = { N1, N2, N3, N3, N1 };
static const uint8_t del_p2[5] = { N2, N1, N2, N1, N3 };

static void noeud_hiz(void)
{
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    TRISAbits.TRISA6 = 1;
}

static void noeud_sortie(uint8_t noeud, uint8_t niveau)
{
    switch (noeud) {
        case N1: LATCbits.LATC0 = niveau; TRISCbits.TRISC0 = 0; break;
        case N2: LATCbits.LATC1 = niveau; TRISCbits.TRISC1 = 0; break;
        case N3: LATAbits.LATA6 = niveau; TRISAbits.TRISA6 = 0; break;
        default: break;
    }
}

void DEL_Init(void)
{
    ANSELAbits.ANSA6 = 0;   /* RA6 en numérique (analogique par défaut dans MCC) */
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATAbits.LATA6 = 0;
    noeud_hiz();
}

void DEL_Allume(uint8_t n)
{
    uint8_t anode, cathode;

    noeud_hiz();
    if (n == 0u || n > 5u) {
        return;
    }
#if DEL_PASTILLE1_ANODE
    anode = del_p1[n - 1u];
    cathode = del_p2[n - 1u];
#else
    anode = del_p2[n - 1u];
    cathode = del_p1[n - 1u];
#endif
    noeud_sortie(cathode, 0);
    noeud_sortie(anode, 1);
}
