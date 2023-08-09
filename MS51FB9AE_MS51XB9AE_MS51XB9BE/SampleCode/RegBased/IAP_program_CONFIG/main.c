/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"


/*---------------------------------------------------------------
 * Try to avoid modify CONFIG in the program
 * NEVER modify config immediately after RESET
//---------------------------------------------------------------*/

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
    while(GPIO_LED);

    if(PCON&SET_BIT4)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
       Modify_CONFIG(0xEF,0xFF,0x6B,0xFF,0xFF);
       PCON&=CLR_BIT4;      /* Clear power on flag to avoid software reset modify CONFIG again. */
    }

    while(1);
}
//-----------------------------------------------------------------------------------------------------------
