/*
 * veille.c
 *
 * Réveil par interrupt-on-change (IOC) sur RA5. L'ISR générée par MCC ne
 * gère pas l'IOC : on dort donc avec GIE = 0. Le PIC se réveille quand même
 * sur IOCIF (avec IOCIE = 1), mais sans aller dans l'ISR, et l'exécution
 * reprend juste après l'instruction SLEEP.
 */
#include "veille.h"
#include "del.h"
#include "lis2hh12.h"
#include "../mcc_generated_files/system/system.h"

void VEILLE_Init(void)
{
    ANSELAbits.ANSA7 = 0;   /* RA7 en numérique */
    WPUAbits.WPUA7 = 1;     /* pull-up : JP1 ouvert = 1, soudé = 0 */
}

bool VEILLE_Activee(void)
{
    return PORTAbits.RA7 == 0;
}

bool VEILLE_Dormir(void)
{
    /* ---- Tout éteindre ---- */
    DEL_Allume(0);
    (void)LIS2HH12_PowerDown();     /* l'I2C a encore besoin des interruptions */
    LCDCONbits.LCDEN = 0;           /* le contenu de LCDDATAx est conservé */

    /* ---- Réveil sur front descendant de RA5 (S1 appuyé) ---- */
    INTERRUPT_GlobalInterruptDisable();
    IOCANbits.IOCAN5 = 1;
    IOCAFbits.IOCAF5 = 0;
    PIR0bits.IOCIF = 0;
    PIE0bits.IOCIE = 1;

    SLEEP();
    NOP();                          /* instruction exécutée au réveil */

    PIE0bits.IOCIE = 0;
    IOCANbits.IOCAN5 = 0;
    IOCAFbits.IOCAF5 = 0;
    INTERRUPT_GlobalInterruptEnable();

    /* ---- Tout rallumer ---- */
    LCDCONbits.LCDEN = 1;
    __delay_ms(20);                 /* démarrage du LIS2HH12 */
    return LIS2HH12_Init();
}
