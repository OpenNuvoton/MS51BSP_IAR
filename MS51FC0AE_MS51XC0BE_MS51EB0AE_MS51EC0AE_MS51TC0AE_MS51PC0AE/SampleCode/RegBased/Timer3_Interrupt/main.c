/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

/************************************************************************************************************
*    TIMER 3 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x83
__interrupt void Timer3_ISR(void){
  
    PUSH_SFRS;
  	
    clr_T3CON_TF3;
    GPIO_LED ^= 1;                // LEDR1 toggle when interrupt */

    POP_SFRS;
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    
    Timer3_AutoReload_Interrupt_Initial(24,300000);
    ENABLE_TIMER3_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    set_T3CON_TR3;                              //Timer3 run

    while(1);
}

