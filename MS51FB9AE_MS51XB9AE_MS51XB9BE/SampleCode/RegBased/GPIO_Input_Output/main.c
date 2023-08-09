/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

__no_init unsigned char __data temp @ 0x08;
__no_init unsigned char __idata itemp @ 0x90;
__no_init unsigned char __xdata xtemp @ 0x80;

//----------------------------------------------------------------------------------------------//
void main (void)
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
  ALL_GPIO_QUASI_MODE;
  GPIO_LED_QUASI_MODE;
  P13_INPUT_MODE;
  
  while(1)
  {
    P1 = ~P1;
    GPIO_LED ^= 1;
    P1 |= SET_BIT2;    
    if (!(P1&SET_BIT3)) 
    {
      _nop_();
    }
    Timer2_Delay(24000000,4,200,1000);

    P1 &= CLR_BIT2;
    if (P1&SET_BIT3) 
    {
      _nop_();
    }
    Timer2_Delay(24000000,4,200,1000);
  }
}



