/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 read UID demo
//***********************************************************************************************************
#include "MS51_16K_IAR.H"


void main(void)
{
  unsigned char READ1;
  ALL_GPIO_QUASI_MODE;

/* Modify HIRC to 24MHz for UART printf function only */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();

  Read_UID();
  printf_UART("\n UID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf_UART(" 0x%x", UIDBuffer[READ1]);
    _delay_();
    _delay_();
    _delay_();
  }
  
  while(1);


}