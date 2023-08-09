/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


unsigned char temp;
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n Test start ...");

    ENABLE_ADC_CH4;            
  /* ADC Low speed initial*/  
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */
    P17_PUSHPULL_MODE;
 
    while(1)
    {
      Timer2_Delay(24000000,128,100,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp = ADCRH;
      printf ("\n ADCRH Value = 0x%x", temp);
    }
}


