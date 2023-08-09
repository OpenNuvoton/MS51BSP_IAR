/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"

void main(void)
{
  GPIO_LED_QUASI_MODE;
  P01_PUSHPULL_MODE;
  set_CKCON_CLOEN;
/* clock out about  100khz base on HIRC div 160 */
  CKDIV = 80;
  while (1)
  {
    while (P30)
    {
      MODIFY_HIRC(HIRC_16);
      GPIO_LED = 1;
      Timer0_Delay(16000000,5,1000);;
      GPIO_LED = 0;
      Timer0_Delay(16000000,5,1000);
    }
/* HIRC modify to 24 , clock out 150 khz */
    MODIFY_HIRC(HIRC_24);
  }
  
}