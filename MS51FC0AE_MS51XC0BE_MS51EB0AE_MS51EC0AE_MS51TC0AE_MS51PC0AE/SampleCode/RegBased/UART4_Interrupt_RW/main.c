/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: ML51 UART receive and transmit toggle out demo code
//***********************************************************************************************************

#include "MS51_32K_IAR.h"

/**
 * @brief       UART4 TXD output demo
 * @param       None
 * @return      None
 * @details     conned UART2 and UART0 to loop check.
 */

void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    UART4_Open(24000000,115200);                 /* Open UART3 use timer1 as baudrate generate and baud rate = 115200*/
    P23_QUASI_MODE;                              /* Set UART4_TXD pin P2.3 as Quasi mode */
    P22_INPUT_MODE;                              /* Set UART5_RXD pin P2.2 as Input mode */
    ENABLE_UART4_TXD_P23;
    ENABLE_UART4_RXD_P22;

    DISABLE_SC2_TRASMIT_BUFFER_EMPTY_INTERRUPT;
    ENABLE_SC2_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart4rvflag==1)
    {
      uart4rvflag = 0;
      UART4_Send_Data(uart4rvbuffer);
    }
   }
 }