/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
 !!! MS51_8K UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.
 External UART1 connect also disturb debug download
 ***************************************************************************************************************/
void main (void)
{
    P17_PUSHPULL_MODE;                      // For I/O toggle display
/* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;                 //For interrupt enable , interrupt subroutine is in uart.c file
    ENABLE_GLOBAL_INTERRUPT;                //ENABLE_GLOBAL_INTERRUPT

    while(1)
    {
      if (uart1_receive_flag)
      {
          GPIO_LED ^= 1;      //Receive each byte P12 toggle, never work under debug mode
          UART_Send_Data(UART1,uart1_receive_data);
          uart1_receive_flag = 0;
      }
    }
}
  
