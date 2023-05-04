/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 Timer 2 capture function demo                                                       */
//***********************************************************************************************************/
#include "MS51_8K_IAR.h"

/************************************************************************************************************/
/*    Capture interrupt subroutine                                                                   */
/************************************************************************************************************/
#pragma vector=0x63
__interrupt void Capture_ISR (void){
  
    _push_(SFRS);
  
    clr_CAPCON0_CAPF2;                  /* clear capture0 interrupt flag  */
    clr_T2CON_TF2;

    _pop_(SFRS);
}
/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    
    P00_QUASI_MODE;
    P00 = 1;

    TIMER2_Compare_Capture_Mode;
    TIMER2_CAP2_RELOAD_Mode;
    IC3_P00_CAP2_BOTHEDGE_CAPTURE;

    set_EIE_ECAP;                        //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}
