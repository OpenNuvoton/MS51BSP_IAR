/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC simple convert demo code
//***********************************************************************************************************
#include "MS51_32K_IAR.h"
unsigned char  ADC_CONT_FINAL_FLAG; 
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/

void main (void) 
{

    unsigned int temp;

/* Initial UART0 for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART("\n ADC Simple demo ");
    
/* Initial ADC */
    ENABLE_ADC_CH0;
    
    while(1)
    {
      Timer2_Delay(24000000,128,300,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp=(ADCRH<<4);
      temp|=(ADCRL&0x0F);
      printf_UART("\n ADC Value = 0x%x", temp);
      P35 ^= 1;
    }
}


