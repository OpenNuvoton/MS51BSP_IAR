/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x2B
__interrupt void Timer2_ISR(void){
  
    _push_(SFRS);
  
    clr_T2CON_TF2;                 //Clear Timer2 Interrupt Flag
    GPIO_LED ^= 1;                // LEDR1 toggle when interrupt 

    _pop_(SFRS);
}
/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    
    TIMER2_DIV_128;
    TIMER2_Auto_Reload_Delay_Mode;
  
    RCMP2H = 0x60;
    RCMP2L = 0xFF;

    TL2 = 0x60;
    TH2 = 0xFF;

    ENABLE_TIMER2_INTERRUPT;                          // Enable Timer2 interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_T2CON_TR2;                                    // Timer2 run

    while(1)
    {
      set_T2CON_TR2;
    }

}
