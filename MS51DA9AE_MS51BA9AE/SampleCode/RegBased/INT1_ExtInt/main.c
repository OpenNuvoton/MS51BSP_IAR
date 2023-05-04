/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 INT1 extneranl interrupt demo                                                       */
/************************************************************************************************************/
#include "MS51_8K_IAR.h"

/* External pin interrupt INT0 subroutine */
#pragma vector=0x13
__interrupt void INT1_ISR(void){
  
    _push_(SFRS);
  
    clr_TCON_IE1;          //clr int flag wait next falling edge

    _pop_(SFRS);
}

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    P17_QUASI_MODE;                     //setting INT0 pin P1.7 as Quasi mode with internal pull high  
    P17 = 1;
    INT1_LOW_LEVEL_TRIG;                //setting trig condition level or edge
    ENABLE_INT1_INTERRUPT;              //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



