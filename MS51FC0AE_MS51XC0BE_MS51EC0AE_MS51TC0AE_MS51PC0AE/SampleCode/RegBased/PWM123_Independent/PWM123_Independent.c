/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2019                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 PWM simple output demo                                                              */
/************************************************************************************************************/
#include "MS51_32K_IAR.h"


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    P12_PUSHPULL_MODE;
    P11_PUSHPULL_MODE;
    P05_PUSHPULL_MODE;
    P04_PUSHPULL_MODE;
    P32_PUSHPULL_MODE;
    P34_PUSHPULL_MODE;


    ENABLE_PWM1_CH0_P12_OUTPUT;
    ENABLE_PWM1_CH1_P11_OUTPUT;
  
    ENABLE_PWM2_CH0_P05_OUTPUT;
    ENABLE_PWM2_CH1_P04_OUTPUT;
  
    ENABLE_PWM3_CH0_P32_OUTPUT;
    ENABLE_PWM3_CH1_P34_OUTPUT;

/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x3FF + 1)
                = 2.7KHz
***********************************************************************/
    PWM1_CLOCK_DIV_8;
    PWM2_CLOCK_DIV_4;
    PWM3_CLOCK_DIV_2;

    SFRS = 2;
    PWM1PH = 0x03;                     /*Setting PWM period  */
    PWM1PL = 0xFF;
    PWM1C0H = 0x0;                      /*PWM1 high duty = 1/2 PWM period */
    PWM1C0L = 0xFF;
    PWM1C1H = 0x01;
    PWM1C1L = 0x80;
    set_PWM1CON0_LOAD;
    set_PWM1CON0_PWMRUN;

    SFRS = 2;
    PWM2PH = 0x03;                     /*Setting PWM period  */
    PWM2PL = 0xFF;
    PWM2C0H = 0x01;                      /*PWM1 high duty = 1/2 PWM period */
    PWM2C0L = 0xFF;
    PWM2C1H = 0x02;
    PWM2C1L = 0x80;
    set_PWM2CON0_LOAD;
    set_PWM2CON0_PWMRUN;

    SFRS = 2;
    PWM3PH = 0x03;                     /*Setting PWM period  */
    PWM3PL = 0xFF;
    PWM3C0H = 0x02;                      /*PWM1 high duty = 1/2 PWM period */
    PWM3C0L = 0xFF;
    PWM3C1H = 0x03;
    PWM3C1L = 0x80;
    set_PWM3CON0_LOAD;
    set_PWM3CON0_PWMRUN;
    
    while(1);

}