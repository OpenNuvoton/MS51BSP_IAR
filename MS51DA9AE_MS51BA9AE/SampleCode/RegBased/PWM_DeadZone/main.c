/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


/************************************************************************************************************/
/*    Main function                                                                                         */
/*     PWM4 P0.5 simple output a 2.7KHz 1/4high duty signal                                                 */
/************************************************************************************************************/
void main(void)
{

/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (16MHz/8)/(0x7CF+1) = 1KHz (1ms)
  PWM4 high duty   = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty   = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/16000000 = 32 us (max value)
-----------------------------------------------------------------------------------------------------------------*/
    MODIFY_HIRC(HIRC_24);
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (24MHz/8)/(0x7CF+1) = 1.5KHz (666ms)
  PWM4 high duty   = PWM4H,PWM4L = 0x01CF = 1/4 PWM period
  PWM0 high duty   = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x1FF <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/24000000 = 21.3 us (max value)
-----------------------------------------------------------------------------------------------------------------*/    
    P10_PUSHPULL_MODE;
    P00_PUSHPULL_MODE;
    P01_PUSHPULL_MODE;
    P03_PUSHPULL_MODE;
    
    ENABLE_PWM0_CH2_P10_OUTPUT;
    ENABLE_PWM0_CH3_P00_OUTPUT;
    ENABLE_PWM0_CH4_P01_OUTPUT;
    ENABLE_PWM0_CH5_P03_OUTPUT;

  
    PWM0_COMPLEMENTARY_MODE;          //Only this mode support deat time function
    PWM0_CLOCK_DIV_8;
    PWMPH = 0x07;
    PWMPL = 0xCF;

    PWM2H = 0x03;
    PWM2L = 0xCF;
    set_SFRS_SFRPAGE;                    // PWM4 and PWM5 duty value need set SFPPAGE 1
    PWM4H = 0x01;
    PWM4L = 0xCF;
    clr_SFRS_SFRPAGE;
    
    ENABLE_PWM0_CH23_DEADTIME;
    ENABLE_PWM0_CH45_DEADTIME;
    PWM0_DeadZoneEnable(PWM0_CH01,0x100); //value never over 0x1FF

//Please always setting Dead time if needed before PWM run.    
    set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while(1);    
}