/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 Wakeup timer demo code with interrupt                                               */
/************************************************************************************************************/

#include "MS51_8K_IAR.h"


#pragma vector=0x8B
__interrupt void WKT_ISR(void){
  
    _push_(SFRS);
    
    clr_WKCON_WKTR;
    P17 = 0;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 1;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 0;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 1;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 0;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 1;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 1;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 0;
    Timer2_Delay(16000000,4,5,1000);
    P17 = 1;
    clr_WKCON_WKTF;                                   //clear interrupt flag
    set_WKCON_WKTR;

    _pop_(SFRS);
}  


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
   
    P17_PUSHPULL_MODE;


//-----------------------------------------------------
//  WKT initial   
//-----------------------------------------------------  
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    RWK = 0XFF;                      //  if prescale is 0x00, never set RWK = 0xff
    RWK = 0X00;
    ENABLE_WKT_INTERRUPT;                          // enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_WKCON_WKTR;                         // Wake-up timer run 

    while(1)
    {
      P17 ^= 1;
      Timer0_Delay(16000000,200,1000);
    }
}

