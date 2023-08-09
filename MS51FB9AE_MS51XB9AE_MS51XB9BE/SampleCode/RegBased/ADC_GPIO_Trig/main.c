/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

BIT  adcintflag;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#pragma vector=0x5B
__interrupt void ADC_ISR (void){
    _push_(SFRS);
  
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    adcintflag = 1;
    
    _pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ... \n\r ");
    printf ("\n\r Toggle P04 to low to start ADC ... \n\r  ");

/*---------------------------------------------------------------
  ADC port trig initial setting toggle P0.4 to start ADC 
----------------------------------------------------------------*/
    ENABLE_ADC_AIN0;                              // Enable AIN0 P1.7 as ADC pin
    P04_QUASI_MODE;
    P04_FALLINGEDGE_TRIG_ADC;                     // P0.4 falling edge as adc start trig signal
/* Enable ADC interrupt */
    ENABLE_ADC_INTERRUPT;                         // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
/* Trig P04 falling edge to start adc, no need set ADCS bit*/
    while(1)                                      // Wait ADC interrupt
    {
      if (adcintflag)
      {
            printf (" \n\r  Value = 0x%x",ADCRH);
            adcintflag =0;
      }
    }
}


