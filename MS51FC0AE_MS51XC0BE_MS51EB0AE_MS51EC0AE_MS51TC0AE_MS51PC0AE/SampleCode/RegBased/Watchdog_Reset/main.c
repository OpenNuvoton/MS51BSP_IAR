/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Watchdog timer interrupt function demo                                              */
/************************************************************************************************************/
#include "ms51_32k_iar.h"

void main (void)
{
    set_WDCON_WDCLR;
/* Note WDT timer base is LIRC 10Khz*/
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    
    printf (" \n\r  Enable WDT in CONFIG  \n\r ");
    set_WDCON_WDCLR;
    printf (" \n\r  Test start MCU reset  \n\r ");
    set_WDCON_WDCLR;
    printf (" \n\r  P35 connect to VSS, WDT not reset  \n\r ");
    set_WDCON_WDCLR;
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    WDT_Open(256);
    WDT_Interrupt(Disable);
    ENABLE_GLOBAL_INTERRUPT;
    while (!GPIO_LED)
    {
      set_WDCON_WDCLR;
      Timer0_Delay(24000000,800,1000);
    }

}
