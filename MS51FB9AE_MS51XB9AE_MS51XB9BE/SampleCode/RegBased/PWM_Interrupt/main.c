/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

BIT  pwm0flag;
/************************************************************************************************************/
/*   PWM interrupt subroutine                                                                               */
/************************************************************************************************************/
#pragma vector=0x6B
__interrupt void INT0_ISR(void){
  
    _push_(SFRS);
  
    clr_PWMCON0_PWMF;               // clear PWM interrupt flag
    pwm0flag = 1;
    
    _pop_(SFRS);
}	

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (24MHz/8)/(0x3FF + 1)
                = 2.93KHz
***********************************************************************/
    P10_QUASI_MODE;
    PWM2_P10_OUTPUT_ENABLE;
    PWM_INT_PWM2;  
    PWM_FALLING_INT;          /*Setting Interrupt happen when PWM0 falling signal */
  
    PWM_CLOCK_DIV_8;
    PWMPH = 0x03;              /*Setting PWM period  */
    PWMPL = 0xFF;
    PWM2H = 0x00;              /*PWM0 high duty  */
    PWM2L = 0xFF;  

    ENABLE_PWM0_INTERRUPT;     /*Enable PWM interrupt  */
    ENABLE_GLOBAL_INTERRUPT;                  
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1)
    {
      if (pwm0flag)
      {
        printf (" \n\r  PWM interrupt!  \n\r  ");
        pwm0flag = 0;
      }
    }
}