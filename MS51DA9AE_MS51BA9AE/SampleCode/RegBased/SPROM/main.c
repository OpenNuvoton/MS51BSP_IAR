/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MS51_8K_IAR.h"
#include "SPROM.h"

const __code char lockdata@0xFFFF = 0x5A;  /* This byte as 0xFF means unlock SPROM. Any other value is lock*/

unsigned char SPTEMP=0;

void main (void) 
{
    unsigned char temp;
    
    ENABLE_SPROM_ACCESS;             //Enable SPROM memory mapping only for check SPROM in memory window 
  
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART ("\n Test start ...");
    
    printf_UART("\n SPROM lock byte = 0x%x ", lockdata);
    while(1)
    {
      temp = SPROM_FUNC(SPTEMP);
      ENABLE_UART0_PRINTF;
      printf_UART("\n SPTEMP= 0x%x", temp);
      Timer0_Delay(24000000,300,1000);
    }

}
