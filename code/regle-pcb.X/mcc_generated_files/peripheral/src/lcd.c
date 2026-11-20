/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../lcd.h"

// Set the LCD module to the options selected in the user interface.
void LCD_Initialize(void) {
    // LCDEN enabled; SLPEN enabled; WERR No LCD Write Error; CS LFINTOSC; LMUX 1/4 COM(3:0); 
    LCDCON = 0x84;
    // WFT Type-A waveform; LP 1:4; 
    LCDPS = 0x3;
    // LPEN disabled; EN5V disabled; BIAS 2.80V; 
    LCDVCON1 = 0x0;
    // LCWDIS enabled; LCDVSRC Internal Resistor Ladder + Vdd for VLCD3; 
    LCDVCON2 = 0x2;
    // LCDCST Max contrast (Min Resistance); 
    LCDREF = 0x0;
    // LRLAP High; LRLBP Low; LCDIRI disabled; LRLAT A power 2, B power 14; 
    LCDRL = 0xD2;
    // SE07 disabled; SE06 disabled; SE05 disabled; SE04 disabled; SE03 enabled; SE02 enabled; SE01 enabled; SE00 enabled; 
    LCDSE0 = 0xF;
    // SE15 disabled; SE14 disabled; SE13 disabled; SE12 disabled; SE11 enabled; SE10 enabled; SE09 enabled; SE08 enabled; 
    LCDSE1 = 0xF;
    // SE23 disabled; SE22 disabled; SE21 disabled; SE20 disabled; SE19 disabled; SE18 disabled; SE17 disabled; SE16 disabled; 
    LCDSE2 = 0x0;
    // SE31 disabled; SE30 disabled; SE29 disabled; SE28 disabled; SE27 disabled; SE26 disabled; SE25 disabled; SE24 disabled; 
    LCDSE3 = 0x0;
    // SE39 disabled; SE38 disabled; SE37 disabled; SE36 disabled; SE35 disabled; SE34 disabled; SE33 disabled; SE32 disabled; 
    LCDSE4 = 0x0;
    // SE47 disabled; SE46 disabled; SE45 disabled; SE44 disabled; SE43 disabled; SE42 disabled; SE41 disabled; SE40 disabled; 
    LCDSE5 = 0x0;
    // S07C0 disabled; S06C0 disabled; S04C0 disabled; S03C0 disabled; S02C0 disabled; S01C0 disabled; S00C0 disabled; 
    LCDDATA0 = 0x0;
    // S15C0 disabled; S14C0 disabled; S13C0 disabled; S11C0 disabled; S10C0 disabled; S09C0 disabled; S08C0 disabled; 
    LCDDATA1 = 0x0;
    // S23C0 disabled; S22C0 disabled; S20C0 disabled; S19C0 disabled; S18C0 disabled; 
    LCDDATA2 = 0x0;
    // S07C1 disabled; S06C1 disabled; S04C1 disabled; S03C1 disabled; S02C1 disabled; S01C1 disabled; S00C1 disabled; 
    LCDDATA6 = 0x0;
    // S15C1 disabled; S14C1 disabled; S13C1 disabled; S11C1 disabled; S10C1 disabled; S09C1 disabled; S08C1 disabled; 
    LCDDATA7 = 0x0;
    // S23C1 disabled; S22C1 disabled; S20C1 disabled; S19C1 disabled; S18C1 disabled; 
    LCDDATA8 = 0x0;
    // S07C2 disabled; S06C2 disabled; S04C2 disabled; S03C2 disabled; S02C2 disabled; S01C2 disabled; S00C2 disabled; 
    LCDDATA12 = 0x0;
    // S15C2 disabled; S14C2 disabled; S13C2 disabled; S11C2 disabled; S10C2 disabled; S09C2 disabled; S08C2 disabled; 
    LCDDATA13 = 0x0;
    // S23C2 disabled; S22C2 disabled; S20C2 disabled; S19C2 disabled; S18C2 disabled; 
    LCDDATA14 = 0x0;
    // S07C3 disabled; S06C3 disabled; S04C3 disabled; S03C3 disabled; S02C3 disabled; S01C3 disabled; S00C3 disabled; 
    LCDDATA18 = 0x0;
    // S15C3 disabled; S14C3 disabled; S13C3 disabled; S11C3 disabled; S10C3 disabled; S09C3 disabled; S08C3 disabled; 
    LCDDATA19 = 0x0;
    // S23C3 disabled; S22C3 disabled; S20C3 disabled; S19C3 disabled; S18C3 disabled; 
    LCDDATA20 = 0x0;
    // S07C4 disabled; S06C4 disabled; S04C4 disabled; S03C4 disabled; S02C4 disabled; S01C4 disabled; S00C4 disabled; 
    LCDDATA24 = 0x0;
    // S15C4 disabled; S14C4 disabled; S13C4 disabled; S11C4 disabled; S10C4 disabled; S09C4 disabled; S08C4 disabled; 
    LCDDATA25 = 0x0;
    // S23C4 disabled; S22C4 disabled; S20C4 disabled; S19C4 disabled; S18C4 disabled; 
    LCDDATA26 = 0x0;
    // S07C5 disabled; S06C5 disabled; S04C5 disabled; S03C5 disabled; S02C5 disabled; S01C5 disabled; S00C5 disabled; 
    LCDDATA30 = 0x0;
    // S15C5 disabled; S14C5 disabled; S13C5 disabled; S11C5 disabled; S10C5 disabled; S09C5 disabled; S08C5 disabled; 
    LCDDATA31 = 0x0;
    // S23C5 disabled; S22C5 disabled; S20C5 disabled; S19C5 disabled; S18C5 disabled; 
    LCDDATA32 = 0x0;
    // S07C6 disabled; S06C6 disabled; S04C6 disabled; S03C6 disabled; S02C6 disabled; S01C6 disabled; S00C6 disabled; 
    LCDDATA36 = 0x0;
    // S15C6 disabled; S14C6 disabled; S13C6 disabled; S11C6 disabled; S10C6 disabled; S09C6 disabled; S08C6 disabled; 
    LCDDATA37 = 0x0;
    // S23C6 disabled; S22C6 disabled; S20C6 disabled; S19C6 disabled; S18C6 disabled; 
    LCDDATA38 = 0x0;
    // S07C7 disabled; S06C7 disabled; S04C7 disabled; S03C7 disabled; S02C7 disabled; S01C7 disabled; S00C7 disabled; 
    LCDDATA42 = 0x0;
    // S15C7 disabled; S14C7 disabled; S13C7 disabled; S11C7 disabled; S10C7 disabled; S09C7 disabled; S08C7 disabled; 
    LCDDATA43 = 0x0;
    // S23C7 disabled; S22C7 disabled; S20C7 disabled; S19C7 disabled; S18C7 disabled; 
    LCDDATA44 = 0x0;
}
