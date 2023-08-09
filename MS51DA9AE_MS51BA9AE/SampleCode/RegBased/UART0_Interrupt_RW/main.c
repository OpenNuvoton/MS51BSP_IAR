/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_INTERRUPT;                                  /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */
  

/* IMPORTANT Notice: 
   1. MS51 8K tiny baord P2.0 connect reset pull high resister, must be removed  
   2. nRESET pin must setting as GPIO mode in CONFIG
   3. Remove ICE reset pin connect 
   then test UART0 input function .
*/
   DISABLE_UART0_INTERRUPT;
   printf ("\n\r UART RX pin also is RESET pin \n\r ");
   printf ("\n\r Remove pull high resister to test UART0 Receive funciton! \n\r ");
   DISABLE_UART0_PRINTF;
   ENABLE_UART0_INTERRUPT; 
   
/* Main loop*/
  while(1)
  {
    if (uart0_receive_flag)
    {
      uart0_receive_flag = 0;
      DISABLE_UART0_INTERRUPT;
      UART_Send_Data(UART0,uart0_receive_data);
      ENABLE_UART0_INTERRUPT;
    }
  }
}