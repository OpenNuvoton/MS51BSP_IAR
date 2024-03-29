/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"


void main(void)
{
  unsigned char READ1;

/* UART0 initial setting*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    
/* Read UID*/
  Read_UID();
  printf(" \n\r  UID = ");
  for(READ1=0;READ1<12;READ1++)
  {
    printf(" 0x%x",UIDBuffer[READ1]);
  }

  while(1);


}