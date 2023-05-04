/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 modify HIRC demo
//***********************************************************************************************************
#include "MS51_16K_IAR.H"

void main(void)
{
  P11_PUSHPULL_MODE;
  P12_PUSHPULL_MODE;
  set_CKCON_CLOEN;
/* clock out div 100 */
  CKDIV = 50;
  while (P20)
  {
    MODIFY_HIRC(HIRC_16);
    P12 = 1;
    Timer0_Delay(16000000,5,1000);;
    P12 = 0;
    Timer0_Delay(16000000,5,1000);
  }
/* HIRC modify to 24MHz  */
  MODIFY_HIRC(HIRC_24);
  while(1);
  
}