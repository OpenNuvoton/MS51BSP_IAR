/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

BIT adcintflag;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#pragma vector=0x5B
__interrupt void ADC_ISR (void){
  
    _push_(SFRS);
  
    clr_ADCCON0_ADCF;                       // Clear ADC interrupt flag
    adcintflag =1;

    _pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{

/* Initial UART0 for printf */

/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
#if 0
// By PWM falling edge
    PWM4_P01_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM4_FALLINGEDGE_TRIG_ADC;  
#endif    
#if 1
// By PWM rising edge
    PWM4_P01_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM4_RISINGEDGE_TRIG_ADC;
#endif    
#if 0
// By PWM central point
    PWM4_P01_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM4_CENTRAL_TRIG_ADC;  
#endif  
#if 0
// By PWM end point
    PWM4_P01_OUTPUT_ENABLE;        
    ENABLE_ADC_AIN0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM4_END_TRIG_ADC;
#endif  
  
// Setting PWM value
    PWMPH = 0x07;                                //Setting PWM value          
    PWMPL = 0xFF;
    set_SFRS_SFRPAGE;            //PWM4 and PWM5 duty seting is in SFP page 1
    PWM4H = 0x02;
    PWM4L = 0xFF;
    PWM_CLOCK_DIV_128;
    set_PWMCON0_LOAD;                                    // PWM run
    set_PWMCON0_PWMRUN;
// Setting ADC
    ENABLE_ADC_INTERRUPT;                                    // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
    adcintflag = 0;
    while(1)
    {
      if (adcintflag)
      {
        printf( "\n ADCRH = 0x%x", ADCRH);
        adcintflag = 0;
      }
    }

}


