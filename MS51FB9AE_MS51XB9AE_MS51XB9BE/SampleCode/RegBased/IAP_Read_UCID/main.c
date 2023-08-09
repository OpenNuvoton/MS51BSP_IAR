/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"


/***********************/
/* main loo    */
/***********************/ 
void main(void)
{
  unsigned char READ1;
  
/* Modify HIRC to 24MHz for UART printf function only */
  MODIFY_HIRC(HIRC_24);
  Enable_UART0_VCOM_printf_24M_115200();

  Read_UCID();
  printf (" \n\r  UCID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf(" \r 0x%x",UCIDBuffer[READ1]);
  }

  while(1);


}