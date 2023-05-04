/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 Clock out from CLKO pin P1.1 demo.
//***********************************************************************************************************
#include "MS51_16K_IAR.H"


void main(void)
{

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART ("\n Test start ...");
    printf_UART ("\nPlease measure P1.1 (CLKO) pin for system clock output.");
    
 /* Note
       MCU power on system clock is HIRC (16.0000MHz), if need change Fsys source pleaes copy hange system closk source demo
*/
    P11_PUSHPULL_MODE;                    /* P11 CLKO pin setting push pull mode to check output. */
    set_CKCON_CLOEN;                      /*System Clock Output Enable */

    CKDIV = 50;                          /*SYS clock divider 100 output */
/*Please measure P1.1 (CLKO) pin for system clock output, it should as system clock;    */
    while(1)
    {
       /* 16MHz HIRC clock out demo */
       MODIFY_HIRC(HIRC_166);
       Timer0_Delay(16600000,100,1000);
       /* 24MHz HIRC clock out demo */
       MODIFY_HIRC(HIRC_24);
       Timer0_Delay(24000000,100,1000);
    }
}

