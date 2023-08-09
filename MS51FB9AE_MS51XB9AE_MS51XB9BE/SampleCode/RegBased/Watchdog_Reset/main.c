/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"
 

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    set_WDCON_WDCLR;
/* Note WDT timer base is LIRC 10Khz*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    
    printf (" \n\r  Enable WDT in CONFIG  \n\r ");
    set_WDCON_WDCLR;
    printf (" \n\r  Test start MCU reset  \n\r ");
    set_WDCON_WDCLR;
    printf (" \n\r  P17 connect to VSS, WDT not reset  \n\r ");
    set_WDCON_WDCLR;
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    P17_QUASI_MODE;
    WDT_Open(256);
    WDT_Interrupt(Disable);
    ENABLE_GLOBAL_INTERRUPT;
    while (!P17)
    {
      set_WDCON_WDCLR;
    }

}
