/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

#define  UART2_P03_P04

/**
 * @brief       Main loop
 * @param       None
 * @return      None
 * @details     UART2 printf send data.
 */
void main (void) 
{
/* Modify HIRC to 24MHz is for UART baud rate deviation not over 1% */
    MODIFY_HIRC(HIRC_24);

#ifdef        UART2_P03_P04
    P03_QUASI_MODE;                              /* Set UART2_TXD pin P0.3 as Quasi mode */
    ENABLE_UART2_TXD_P03;
#elif defined UART2_P30_P17
    P30_QUASI_MODE;                              /* Set UART2_TXD pin P3.0 as Quasi mode */
    ENABLE_UART2_TXD_P30;
#endif

    UART2_Open(24000000,115200);
    while(1)
    {
      printf("\n\r Hello world! \n\r");
      Timer0_Delay(24000000,300,1000);
    }
}