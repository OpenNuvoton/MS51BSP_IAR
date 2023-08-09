/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "ms51_32k_iar.h"
#include "sprom_code.h"

__code const char lockdata@0xFFFF = 0x00;  /* This byte as 0xFF means unlock SPROM. Any other value is lock*/

unsigned char SPTEMP=0;

void main (void) 
{
    unsigned char temp;
    
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    UART_Open(24000000,UART0_Timer1,115200);
    printf(" \n\r  SPROM lock byte = 0x%x ", lockdata);
    while(1)
    {
      temp = SPROM_FUNC(SPTEMP);
      ENABLE_UART0_PRINTF;
      printf(" \n\r  SPTEMP= 0x%x", temp);
      DISABLE_UART0_PRINTF;
      Timer0_Delay(24000000,300,1000);
    }

}
