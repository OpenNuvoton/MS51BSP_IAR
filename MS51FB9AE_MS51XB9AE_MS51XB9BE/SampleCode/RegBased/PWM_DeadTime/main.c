/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/************************************************************************************************************/
/*  File Function: MS51 PWM insert dead time demo code                                                      */
/************************************************************************************************************/
#include "MS51_16K_IAR.H"


/************************************************************************************************************/
/*    Main function                                                                                         */
/*     PWM4 P0.5 simple output a 2.7KHz 1/4high duty signal                                                 */
/************************************************************************************************************/
void main(void)
{
    ALL_GPIO_QUASI_MODE;
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (16MHz/8)/(0x7CF+1) = 1KHz (1ms)
  PWM4 high duty  = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty  = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/16000000 = 32 us (max value)
-----------------------------------------------------------------------------------------------------------------*/
    MODIFY_HIRC(HIRC_24);
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (24MHz/8)/(0x7CF+1) = 1.5KHz (666ms)
  PWM4 high duty  = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty  = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/246000000 = 21 us (max value)
-----------------------------------------------------------------------------------------------------------------*/    
    
    PWM0_P12_OUTPUT_ENABLE;
    PWM1_P11_OUTPUT_ENABLE;
    PWM4_P01_OUTPUT_ENABLE;
    PWM5_P15_OUTPUT_ENABLE;
  
    PWM_COMPLEMENTARY_MODE;          //Only this mode support deat time function
    PWM_CLOCK_DIV_8;
    PWMPH = 0x07;
    PWMPL = 0xCF;

    PWM0H = 0x03;
    PWM0L = 0xCF;
    set_SFRS_SFRPAGE;                    // PWM4 and PWM5 duty value need set SFPPAGE 1
    PWM4H = 0x01;
    PWM4L = 0xCF;
    clr_SFRS_SFRPAGE;

    PWM0_DeadZoneEnable(PWM0_CH01,0x1FF);//value never over 0x1FF
    
//Please always setting Dead time if needed before PWM run.    
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);    
}