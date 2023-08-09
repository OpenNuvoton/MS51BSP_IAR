/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

unsigned char uart_receive_data;
unsigned char receiveFlag,bufOverFlag;


#pragma vector=0x23
__interrupt void SerialPort0_ISR(void){

    _push_(SFRS);
  
    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }

    if (TI)
    {
        if (!PRINTFG)
        {
            TI = 0;
        }
    }

    _pop_(SFRS);
}	

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
    ENABLE_UART0_INTERRUPT;                                  /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                 /* Global interrupt enable */
    
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      GPIO_LED ^= 1;
      DISABLE_UART0_INTERRUPT;
      UART_Send_Data(UART0,uart0_receive_data);
      uart0_receive_flag = 0;
      ENABLE_UART0_INTERRUPT;
    }
  }
}