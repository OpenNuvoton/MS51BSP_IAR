/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

/**
 * @brief       UART0 interrupt vector
 * @param       None
 * @return      None
 * @details     UART0 store received data.
 */
#pragma vector=0x23
__interrupt void UART0_ISR(void){
  
    PUSH_SFRS;
    
      if (RI)
    {   
      uart0_receive_flag = 1;
      uart0_receive_data = SBUF;
      clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if  (TI)
    {
      if(!PRINTFG)
      {
          clr_SCON_TI;
      }
    }

    POP_SFRS;
}

/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART0 send received data.
 */
 void main(void)
{

/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24); 
    Enable_UART0_VCOM_printf_24M_115200();

    ENABLE_UART0_INTERRUPT;                                   /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
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