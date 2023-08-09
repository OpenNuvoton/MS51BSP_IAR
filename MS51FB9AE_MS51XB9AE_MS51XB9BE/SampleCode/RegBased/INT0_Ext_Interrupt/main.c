/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

BIT  int0flag;
/* External pin interrupt INT0 subroutine */
#pragma vector=0x03
__interrupt void INT0_ISR(void){
  
    _push_(SFRS);
  
    clr_TCON_IE0;          //clr int flag wait next falling edge
    int0flag =1;
    
    _pop_(SFRS);
}


void main (void) 
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
  
    P30_QUASI_MODE;                      //setting INT0 pin P3.0 as Quasi mode with internal pull high  
    P30 = 1;
    INT0_FALLING_EDGE_TRIG;              //setting trig condition level or edge
    ENABLE_INT0_INTERRUPT;               //INT0_Enable;
    ENABLE_GLOBAL_INTERRUPT;             //Global interrupt enable
    int0flag = 0;
    while(1)
    {
      if (int0flag)
      {
         printf (" \n\r  INT0 interrupt !  \n\r ");
         int0flag = 0;
      }
    }
}



