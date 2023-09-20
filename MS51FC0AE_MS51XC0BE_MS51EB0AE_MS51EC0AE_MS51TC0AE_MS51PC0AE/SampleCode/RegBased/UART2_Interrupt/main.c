/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

#define  UART2_P30_P17

/**
 * @brief       SC0 / UART2 interrupt  vector
 * @param       None
 * @return      None
 * @details     UART2 send received data loop.
 */
#pragma vector=0xAB
__interrupt void SC0_ISR(void){
    PUSH_SFRS;
        uart2rvflag = 1;
        SFRS = 2;
        uart2rvbuffer = SC0DR;
    POP_SFRS;
}


/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART2 send received data loop.
 */
void main (void) 
{
    MODIFY_HIRC(HIRC_24);

#ifdef        UART2_P03_P04
    P03_QUASI_MODE;                              /* Set UART2_TXD pin P0.3 as Quasi mode */
    P04_INPUT_MODE;                              /* Set UART2_RXD pin P0.4 as Input mode */
    ENABLE_UART2_TXD_P03;
    ENABLE_UART2_RXD_P04;
#elif defined UART2_P30_P17
    P30_QUASI_MODE;                              /* Set UART2_TXD pin P3.0 as Quasi mode */
    P17_INPUT_MODE;                              /* Set UART2_RXD pin P1.7 as Input mode */
    ENABLE_UART2_TXD_P30;
    ENABLE_UART2_RXD_P17;
#endif 
    UART2_Open(24000000,115200);                 /* Open UART2 use timer1 as baudrate generate and baud rate = 115200*/
    ENABLE_SC0_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

/* while receive data from RXD, send this data to TXD */
  while(1) 
  {
    if (uart2rvflag)
    {
      uart2rvflag = 0;
      UART2_Send_Data(uart2rvbuffer);
    }
  }

}
