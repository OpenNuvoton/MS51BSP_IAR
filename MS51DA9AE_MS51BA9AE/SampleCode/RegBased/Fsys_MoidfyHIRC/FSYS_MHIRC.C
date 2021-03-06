/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.       */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2019                                                                                   */
/***********************************************************************************************************/

//***********************************************************************************************************
//  File Function: MS51 modify HIRC demo
//***********************************************************************************************************
#include "MS51_8K_IAR.h"

void main(void)
{
  P17_PUSHPULL_MODE;
  P01_PUSHPULL_MODE;
  set_CKCON_CLOEN;
/* clock out about  100khz base on HIRC div 160 */
  CKDIV = 0X50;
  while (1)
  {
    while (P30)
    {
      MODIFY_HIRC_16();
      P17 = 1;
      Timer0_Delay(16000000,5,1000);;
      P17 = 0;
      Timer0_Delay(16000000,5,1000);
    }
/* HIRC modify to 24 , clock out 150 khz */
    MODIFY_HIRC_24();
  }
  
}