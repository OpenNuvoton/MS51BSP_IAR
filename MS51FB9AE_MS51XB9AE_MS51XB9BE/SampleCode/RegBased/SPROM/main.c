/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"
#include "sprom.h"

__code const char lockdata@0xFFFF = 0xFF;  /* This byte as 0xFF means unlock SPROM. Any other value is lock*/

unsigned char SPTEMP=0;

void main (void) 
{
    unsigned char temp;
    
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    printf(" \n\r  SPROM lock byte = 0x%x ", lockdata);
    
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window

    while(1)
    {
      temp = SPROM_FUNC(SPTEMP);
      ENABLE_UART0_PRINTF;
      printf(" \n\r  SPTEMP= 0x%x ", temp);
      Timer0_Delay(24000000,300,1000);
    }

}
