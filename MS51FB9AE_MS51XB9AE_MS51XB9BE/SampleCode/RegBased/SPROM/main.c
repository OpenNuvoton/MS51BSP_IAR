/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MS51_16K_IAR.h"
#include "SPROM.h"

__code const char lockdata@0xFFFF = 0xFF;  /* This byte as 0xFF means unlock SPROM. Any other value is lock*/

unsigned char SPTEMP=0;

void main (void) 
{
    unsigned char temp;
    
    MODIFY_HIRC(HIRC_24);
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    UART_Open(24000000,UART0_Timer1,115200);
    printf_UART("\n SPROM lock byte = 0x%x ", lockdata);
    while(1)
    {
      temp = SPROM_FUNC(SPTEMP);
      ENABLE_UART0_PRINTF;
      printf_UART("\n SPTEMP= 0x%x", temp);
      DISABLE_UART0_PRINTF;
      Timer0_Delay(24000000,300,1000);
    }

}
