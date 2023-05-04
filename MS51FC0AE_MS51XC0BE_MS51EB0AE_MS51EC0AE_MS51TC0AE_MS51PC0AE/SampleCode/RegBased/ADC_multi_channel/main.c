/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: ML56 ADC multi channel input demo code
//***********************************************************************************************************
#include "MS51_32K_IAR.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function

unsigned int __xdata ADCdataAIN5;
unsigned int __xdata ADCdataVBG;

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    unsigned char i;
    MODIFY_HIRC(HIRC_24);
#ifdef print_function
    Enable_UART0_VCOM_printf_24M_115200();
#endif

  /*Enable channel 5 */ 
      ENABLE_ADC_CH5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */

      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(!(ADCCON0&SET_BIT7)); 
      ADCdataAIN5 = (ADCRH<<4);
      ADCdataAIN5 |= (ADCRL&0x0F);
      DISABLE_ADC;
 #ifdef print_function
  /*printf must in SFR page 0 */
     _push_(SFRS);
     SFRS = 0;
     printf_UART("\n ADC channel 5 = %x", ADCdataAIN5);
    _pop_(SFRS);
#endif

  /*Enable Bandgap */
      ENABLE_ADC_BANDGAP;
  /* IMPORTANT !!! multi channel convert must delay for ADC maocro ready */ 
      for (i=0;i<10;i++)
      _delay_();
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      AUXR1&=CLR_BIT4;          /* ADC clock high speed */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(!(ADCCON0&SET_BIT7)); 
      ADCdataVBG = (ADCRH<<4);
      ADCdataVBG |= (ADCRL&0x0F);

#ifdef print_function
  /*printf must in SFR page 0 */
     _push_(SFRS);
     SFRS = 0;
     printf_UART("\n ADC channel bandgap = %x", ADCdataVBG);
    _pop_(SFRS);
#endif

    while(1);
}