/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"



/***********************/
/* main loop           */
/***********************/ 
void main(void)
{
  unsigned char u8Counter;

  MODIFY_HIRC(HIRC_24);
  Enable_UART0_VCOM_printf_24M_115200();
  
  Read_UCID();
  
  printf("\n\r UCID = ");
  for(u8Counter=0;u8Counter<12;u8Counter++)
  {
    printf(" 0x%x",UCIDBuffer[u8Counter]);
    _delay_();_delay_();_delay_();_delay_();
  }

  while(1);


}