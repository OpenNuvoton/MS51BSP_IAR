/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

unsigned char __xdata ADCdataAIN5H, ADCdataAIN5L;
unsigned char __xdata ADCdataVBGH, ADCdataVBGL;

/*****************************************************************************/
/*The main C function.  Program execution starts                             */
/*here after stack initialization.                                           */
/*****************************************************************************/
void main (void) 
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
/*Enable channel 5 */ 
      ENABLE_ADC_AIN5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                                
      while(ADCF == 0);
      ADCdataAIN5H = ADCRH;
      ADCdataAIN5L = ADCRL;
      DISABLE_ADC;
      printf(" \n\r ADC channel 5 =0x%x", ADCdataAIN5H);
      _delay_();
/*Enable Bandgap */     
      ENABLE_ADC_BANDGAP;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(ADCF == 0);
      ADCdataVBGH = ADCRH;
      ADCdataVBGL = ADCRL;
      DISABLE_ADC;
      printf(" \n\r  ADC channel bandgap =0x%x", ADCdataVBGH);

    while(1);  
}