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
 * @brief       UART2 TXD output demo
 * @param       None
 * @return      None
 * @details     conned UART2 and UART0 to loop check.
 */
#define     UART3_P12_P11
void main (void) 
{
    MODIFY_HIRC(HIRC_24);
    
/* UART3 initial */
#ifdef          UART3_P12_P11
    P12_QUASI_MODE;
    P11_INPUT_MODE;
    ENABLE_UART3_TXD_P12;
    ENABLE_UART3_RXD_P11;
#elif  defined   UART3_P15_P25
    P15_QUASI_MODE;
    P25_INPUT_MODE;
    ENABLE_UART3_TXD_P15;
    ENABLE_UART3_RXD_P25;
#elif  defined   UART3_P05_P34
    P05_QUASI_MODE;
    P34_INPUT_MODE;
    ENABLE_UART3_TXD_P05;
    ENABLE_UART3_RXD_P34;
#endif

    UART3_Open(24000000,115200);                 /* Open UART3 use timer1 as baudrate generate and baud rate = 115200*/
    ENABLE_SC1_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart3rvflag)
    {
      uart3rvflag = 0;
      UART3_Send_Data(uart3rvbuffer);
    }
   }
 }