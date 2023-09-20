/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 Time 1 demo
//***********************************************************************************************************
#include "ms51_32k_iar.h"


/* if define TIMER0_FSYS_DIV12, timer = (256-56)*12/16MHz = 150us */
/* if define TIMER0_FSYS, timer = (256-56)/16MHz = 12.5us */
#define TH1_INIT        56 
#define TL1_INIT        56

/************************************************************************************************************
*    TIMER 1 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x1B
__interrupt void INT0_ISR(void){
  
    PUSH_SFRS;
  
    GPIO_LED ^= 1;                /* LEDR1 toggle when interrupt */
  
    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    
    ENABLE_TIMER1_MODE2;
    TIMER1_FSYS_DIV12;
  
    TH1 = TH1_INIT;            //initial counter values 
    TL1 = TL1_INIT;    
   
    ENABLE_TIMER1_INTERRUPT;                                    //enable Timer1 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR1;                                  //Timer1 run

    while(1);
}

