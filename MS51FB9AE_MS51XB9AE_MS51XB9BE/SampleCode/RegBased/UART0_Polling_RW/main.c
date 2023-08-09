/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

unsigned char uart_receive_data;
BIT receivePollingFlag,bufOverFlag;


/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{
    P12_PUSHPULL_MODE;
/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    P06_QUASI_MODE;
    P07_INPUT_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    uart_receive_data = Receive_Data(UART0);
    UART_Send_Data(UART0,uart_receive_data);
   }
}