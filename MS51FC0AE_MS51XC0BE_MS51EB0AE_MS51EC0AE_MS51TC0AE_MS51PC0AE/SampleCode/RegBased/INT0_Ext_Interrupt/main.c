/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 INT0 pin external interrupt demo                                                    */
/************************************************************************************************************/
#include "ms51_32k_iar.h"

/* External pin interrupt INT0 subroutine */
#pragma vector=0x03
__interrupt void INT0_ISR(void){

    PUSH_SFRS;
  
    clr_TCON_IE0;          //clr int flag wait next falling edge
    GPIO_LED ^= 1;
  
    POP_SFRS;
}


void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    
    GPIO_LED_QUASI_MODE;;
    P30_INPUT_MODE;                      //setting INT0 pin P3.0 as Quasi mode with internal pull high
    P30_PULLUP_ENABLE;
    P30 = 1;
    INT0_FALLING_EDGE_TRIG;              //setting trig condition level or edge
    ENABLE_INT0_INTERRUPT;                         //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;            //Global interrupt enable
    while(1);
}



