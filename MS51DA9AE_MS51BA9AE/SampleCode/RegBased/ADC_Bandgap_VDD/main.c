/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
double  Bandgap_Voltage,VDD_Voltage;      //please always use "double" mode for this

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    uint16_t ADC_BG_Result;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...");

/* ADC sampling timing setting for Bandgap*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(ADCF == 0);
/* ADC convert current Bandgap value */
    ADC_BG_Result = ADCRH<<4 ;
    ADC_BG_Result = ADC_BG_Result|(ADCRL&0x0F);
    DISABLE_ADC;              /*Disable ADCEN each time after ADC trig */
    
 /*                  VDD  Now                         READ_BANDGAP() VALUE              */
 /*    ------------------------------------- = ----------------------------------       */
 /*    3072mV(Storage value test condition)      NOW ADC Bandgap convert reuslt         */
      VDD_Voltage = ((float)READ_BANDGAP()/(float)ADC_BG_Result)*3.072;
     
 /*            Bandgap real voltage                    READ_BANDGAP() VALUE             */
 /*    ------------------------------------- = ----------------------------------       */
 /*    3072mV(Storage value test condition)              4096(12bit ADC)                */
     Bandgap_Voltage = ((float)READ_BANDGAP()*3/4/1000);
 
    while(1);
}