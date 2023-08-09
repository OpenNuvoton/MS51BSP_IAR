/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"


/*=============================================================================================*/
/*  The test process:                                                                          */
/*  1. Power on is run as default HIRC, show LED Fsys tickle faster                            */
/*  2. toggle P1.7 to GND. Call modify Fsys code to External clock, oscillator input.          */
/*  3. toggle P1.7 to VDD. Call modify Fsys code to HIRC.                                      */
/*=============================================================================================*/


void main(void)
{

/* Note
  MCU power on system clock is HIRC (16 MHz)
  Please keep P3.0 HIGH before you want to modify Fsys to LIRC
*/
    GPIO_LED_QUASI_MODE; 
    P11_QUASI_MODE;
    set_CKCON_CLOEN;                                  // Also can check P1.1 CLO pin for clock to find the Fsys change.
    while (GPIO_LED);
    FsysSelect(FSYS_OSCIN_P30);
    Timer0_Delay(16000000,200,1000);
    while (!GPIO_LED);
    FsysSelect(FSYS_HIRC);
    Timer0_Delay(16000000,2000,1000);;
    set_PCON_PD;
    while(1);

}

