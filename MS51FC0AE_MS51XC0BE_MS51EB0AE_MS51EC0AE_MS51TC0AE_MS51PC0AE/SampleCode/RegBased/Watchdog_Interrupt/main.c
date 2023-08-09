/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 Watchdog timer interrupt function demo                                              */
/************************************************************************************************************/
#include "ms51_32k_iar.h"

BIT   wdtintflag;
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
#pragma vector=0x53
__interrupt void WDT_ISR(void){
  
_push_(SFRS);

    CLEAR_WDT_INTERRUPT_FLAG;
    GPIO_LED ^= 1;
    wdtintflag = 1;
    
_pop_(SFRS);
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    uint8_t ct; 
/* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
/*--------------------------------------------------------
*Warning:
*Pleaes always check CONFIG WDT disable first 
*only when WDT reset disable, WDT use as pure timer
--------------------------------------------------------*/
    WDT_TIMEOUT_1_6S;                     /* Setting WDT time out */
    WDT_RUN_IN_POWERDOWN_ENABLE;           /* WDT run in POWER DOWM mode setting if needed */
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    WDT_COUNTER_RUN;                       /* WDT start to run */

    for(ct=0;ct<4;ct++)
    {
      WDT_Clear();
      Timer0_Delay(24000000,300,1000);
      GPIO_LED ^= 1;
    }
    while (1)
    {
      if (wdtintflag);
      {
        printf (" \n\r WDT interrupt ! \n\r");
        wdtintflag = 0;
        set_PCON_PD;
      }
    }
}
