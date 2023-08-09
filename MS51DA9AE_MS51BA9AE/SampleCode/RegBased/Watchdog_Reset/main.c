/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"
 

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    set_WDCON_WDCLR;
/* Note WDT timer base is LIRC 10Khz*/
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    
    printf ("\n Enable WDT in CONFIG ");
    set_WDCON_WDCLR;
    printf ("\n Test start MCU reset ");
    set_WDCON_WDCLR;
    printf ("\n P17 connect to VSS, WDT not reset ");
    set_WDCON_WDCLR;
/*--------------------------------------------------------*/
/*IMPORTANT:                                              */
/*Pleaes always check CONFIG WDT ENABLE in CONFIG first   */ 
/*only when WDT reset only works after CONFIG enbale      */
/*--------------------------------------------------------*/

    WDT_Open(512);
    WDT_Interrupt(Disable);
    ENABLE_GLOBAL_INTERRUPT;
    while (!GPIO_LED)
    {
      set_WDCON_WDCLR;
    }

}
