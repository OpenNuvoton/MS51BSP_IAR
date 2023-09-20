/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
#pragma vector=0x5B
__interrupt void INT0_ISR(void){
  
    PUSH_SFRS;
    clr_ADCCON0_ADCF;                       // Clear ADC interrupt flag
    P30 ^= 1;                                // Check the P3.0 toggle at falling edge of PWM
    POP_SFRS;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    MODIFY_HIRC(HIRC_24);
      
    ALL_GPIO_QUASI_MODE;

/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
#if 1
// By PWM falling edge
    ENABLE_PWM0_CH2_P05_OUTPUT;
    ENABLE_ADC_CH0;                            // Enable AIN0 P1.7 as ADC input
    PWM0_CH2_FALLINGEDGE_TRIG_ADC;  
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
    PWM0PH = 0x07;                                //Setting PWM value          
    PWM0PL = 0xFF;
    PWM0C2H = 0x02;
    PWM0C2L = 0xFF;
    set_PWM0CON0_LOAD;                                    // PWM run
    set_PWM0CON0_PWM0RUN;
// Setting ADC
    ENABLE_ADC_INTERRUPT;                                    // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;  
    while(1);

}


