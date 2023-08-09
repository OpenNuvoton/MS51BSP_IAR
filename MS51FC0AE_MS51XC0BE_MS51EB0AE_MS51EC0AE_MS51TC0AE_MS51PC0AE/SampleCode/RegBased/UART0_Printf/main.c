/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: MS51 use UART0 as printf function output demo                                            */
/************************************************************************************************************/
#include "ms51_32k_iar.h"


void main (void) 
{

/* Modify HIRC to 24MHz is for UART baud rate deviation not over 1% */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
  
    while(1)
    {
      printf(" \n\r  Hello world! \n\r");
      Timer0_Delay(24000000,300,1000);
    }
}