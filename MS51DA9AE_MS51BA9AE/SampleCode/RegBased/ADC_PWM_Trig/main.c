/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 ADC PWM trig convert demo code
//***********************************************************************************************************
#include "MS51_8K_IAR.h"

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#pragma vector=0x5B
__interrupt void ADC_ISR (void){
  
_push_(SFRS);
  
    clr_ADCCON0_ADCF;                       // Clear ADC interrupt flag
    P30 ^= 1;                                // Check the P3.0 toggle at falling edge of PWM

_pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;

/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
#if 1
// By PWM falling edge
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_ADC_CH0;                            // Enable AIN0 P1.7 as ADC input
    PWM0_FALLINGEDGE_TRIG_ADC;  
#endif    
#if 0
// By PWM rising edge
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_ADC_CH0;                            // Enable AIN0 P1.7 as ADC input
    PWM0_RISINGEDGE_TRIG_ADC;
#endif    
#if 0
// By PWM central point
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_ADC_CH0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM0_CENTRAL_TRIG_ADC;  
#endif  
#if 0
// By PWM end point
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_ADC_CH0;                            // Enable AIN0 P1.7 as ADC input
    PWM_CENTER_TYPE;
    PWM0_END_TRIG_ADC;
#endif  
  
// Setting PWM value
    PWMPH = 0x07;                                //Setting PWM value          
    PWMPL = 0xFF;
    PWM2H = 0x02;
    PWM2L = 0xFF;
    set_PWMCON0_LOAD;                                    // PWM run
    set_PWMCON0_PWMRUN;
// Setting ADC
    ENABLE_ADC_INTERRUPT;                                    // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;  
    while(1);

}


