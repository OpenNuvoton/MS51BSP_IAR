/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

/* if define TIMER0_FSYS_DIV12, timer = (256-56)*12/246MHz = 100us */
/* if define TIMER0_FSYS, timer = (256-56)/24MHz = 8.33us */
#define TH0_INIT        56 
#define TL0_INIT        56

/***********************************************************************************************************/
/*    TIMER 0 interrupt subroutine                                                                         */
/***********************************************************************************************************/
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){
    _push_(SFRS);
  
    GPIO_LED ^= 1;                                 // GPIO1 toggle when interrup

    _pop_(SFRS);
}	

/************************************************************************************************************/
/*    Main function                                                                                         */
/************************************************************************************************************/
void main (void)
{
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
    ENABLE_TIMER0_MODE2;
    TIMER0_FSYS;
  
    TH0 = TH0_INIT;            //initial counter values 
    TL0 = TL0_INIT;    
   
    ENABLE_TIMER0_INTERRUPT;                       //enable Timer0 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR0;                                    //Timer0 run

    while(1);
}

