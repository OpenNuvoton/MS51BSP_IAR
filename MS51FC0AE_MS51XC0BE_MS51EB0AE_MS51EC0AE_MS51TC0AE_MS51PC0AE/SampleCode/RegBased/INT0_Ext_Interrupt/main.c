/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 INT0 pin external interrupt demo                                                    */
/************************************************************************************************************/
#include "MS51_32K_IAR.h"

/* External pin interrupt INT0 subroutine */
#pragma vector=0x03
__interrupt void INT0_ISR(void){

    _push_(SFRS);
  
    clr_TCON_IE0;          //clr int flag wait next falling edge
    P35 ^= 1;
  
    _pop_(SFRS);
}


void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    
    P35_PUSHPULL_MODE;
    P30_INPUT_MODE;                      //setting INT0 pin P3.0 as Quasi mode with internal pull high
    P30_PULLUP_ENABLE;
    P30 = 1;
    INT0_FALLING_EDGE_TRIG;              //setting trig condition level or edge
     set_IE_EX0;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



