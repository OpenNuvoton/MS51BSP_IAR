/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
    P12_QUASI_MODE;
    P10_QUASI_MODE;
    P01_QUASI_MODE;
    P03_QUASI_MODE;

    PWM0_P12_OUTPUT_ENABLE;
    PWM2_P10_OUTPUT_ENABLE;
    PWM4_P01_OUTPUT_ENABLE;
    PWM5_P03_OUTPUT_ENABLE;
  
    PWM_IMDEPENDENT_MODE;
    PWM_CLOCK_DIV_8;
    PWMPH = 0x30;
    PWMPL = 0x0f;
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x7CF + 1)
                = 1KHz (1ms)
***********************************************************************/

    PWM2H = 0x10;
    PWM2L = 0x08;
    PWM2H = 0x00;
    PWM2L = 0x25;
    
    set_SFRS_SFRPAGE;            //PWM4 and PWM5 duty seting is in SFP page 1
    PWM4H = 0x03;
    PWM4L = 0xCF;
    PWM5H = 0x05;
    PWM5L = 0xCF;
    clr_SFRS_SFRPAGE;
/* PWM output inversly enable */
    PWM2_OUTPUT_INVERSE;

/*-------- PWM start run--------------*/ 
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);

}