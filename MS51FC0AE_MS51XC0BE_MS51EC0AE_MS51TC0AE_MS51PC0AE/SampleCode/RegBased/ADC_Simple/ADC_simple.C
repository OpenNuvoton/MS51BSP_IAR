/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2019
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: MS51 ADC simple convert demo
//***********************************************************************************************************
#include "MS51_32K_IAR.h"

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
unsigned char temp;

void main (void) 
{
/* Initial UART0 for printf */
  
    ENABLE_ADC_CH4;            

  /* ADC Low speed initial*/  
    ADCCON1|=0X30;            /* clock divider */
    ADCCON2|=0X0E;            /* AQT time */
    AUXR1|=SET_BIT4;          /* ADC clock low speed */
    P17_PUSHPULL_MODE;
 
    while(1)
    {
      Timer2_Delay(16000000,128,100,1000);;
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;                  // ADC start trig signal
      while(ADCF == 0);
      temp = ADCRH;
      P17 ^= 1;
    }
}


