/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
//  File Function: MS51 Timer0 mode 2 demo
/************************************************************************************************************/
#include "MS51_32K_IAR.h"


/* if define TIMER0_FSYS_DIV12, timer = (256-56)*12/246MHz = 100us */
/* if define TIMER0_FSYS, timer = (256-56)/24MHz = 8.33us */
#define TH0_INIT        56 
#define TL0_INIT        56

/***********************************************************************************************************/
/*    TIMER 0 interrupt subroutine                                                                         */
/***********************************************************************************************************/
#pragma vector=0x0B
__interrupt void INT0_ISR(void){
  
    _push_(SFRS);
   
    P35 = ~P35;                                 // GPIO1 toggle when interrup
  
    _pop_(SFRS);
}

/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    P35_PUSHPULL_MODE;
    P05_PUSHPULL_MODE;
    set_P0S_5;
    ENABLE_TIMER0_MODE2;
    TIMER0_FSYS;
    set_TOE_T0OE;

    TH0 = TH0_INIT;            //initial counter values 
    TL0 = TL0_INIT;    
   
    ENABLE_TIMER0_INTERRUPT;                       //enable Timer0 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR0;                                    //Timer0 run

    while(1);
}

