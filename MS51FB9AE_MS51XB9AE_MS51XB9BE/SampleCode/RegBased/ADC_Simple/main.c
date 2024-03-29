/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/

unsigned char __xdata ADCdataAINH, ADCdataAINL;

void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");

    ENABLE_ADC_AIN4;            

    while(1)
    {
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);

      printf (" \n\r  ADCRH = 0x%x",ADCRH );
      Timer2_Delay(24000000,128,100,1000);
    }
}


