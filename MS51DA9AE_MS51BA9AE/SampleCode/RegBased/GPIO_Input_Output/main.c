/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"

__no_init unsigned char __data temp @ 0x08;
__no_init unsigned char __idata itemp @ 0x90;
__no_init unsigned char __xdata xtemp @ 0x80;

//----------------------------------------------------------------------------------------------//
void main (void)
{
  MODIFY_HIRC(HIRC_24);
  ALL_GPIO_QUASI_MODE;
  
  while(1)
  {
    P0 = ~ P0;
    P1 = ~ P1;
    if (!(P3&SET_BIT0))        /* if P3.0 == 0 */
    {
      _nop_();
    }
    Timer0_Delay(16000000,100,1000);
    if (P3&SET_BIT0)           /* if P3.0 == 1 */
    {
      _nop_();
    }
    Timer0_Delay(16000000,100,1000);
  }
}



