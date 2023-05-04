/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 power down code for test power down current, BOD disabled.
//***********************************************************************************************************
#include "MS51_8K_IAR.h"


void main (void) 
{
  unsigned char i;
/*Quasi mode better for power down power comsuption */  
    ALL_GPIO_QUASI_MODE;
/* clock only for reference, real chip please don't output clock*/  
    set_CKCON_CLOEN;

/*MUST DISABLE BOD to low power */
    DISABLE_BOD;              //BOD enable power down current please check datasheet DC charactor.
  
    while(P01);
    for (i=0;i<0x05;i++)
    {
      P17 ^= 1;
      Timer0_Delay(16000000,200,1000);
    }
		CKDIV = 0;
      P0=0;
      P1=0;
      P2=0;
      P3=0;
/* Real into power down mode */
    set_PCON_PD;
    while(1);  
  
}



