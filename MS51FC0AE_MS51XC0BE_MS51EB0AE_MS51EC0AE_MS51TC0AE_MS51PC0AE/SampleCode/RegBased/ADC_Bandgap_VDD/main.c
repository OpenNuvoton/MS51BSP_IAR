/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo code                                                  */
//**********************************************************************************************************/

#include "MS51_32K_IAR.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
double  Bandgap_Voltage, VDD_Voltage, Bandgap_Value;      //please always use "double" mode for this
unsigned  char __xdata ADCdataH[5], ADCdataL[5];
int ADCsumH=0, ADCsumL=0;
unsigned char ADCavgH,ADCavgL;


/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
      unsigned int bgvalue;
      unsigned char i=0;
      
/*Read bandgap value */
/* ADC sampling timing setting for Bandgap*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                                
    while(ADCF == 0);
    ADCdataH[i] = ADCRH;
    ADCdataL[i] = ADCRL;
    
/* to convert VDD value */
    bgvalue = ADCRH<<4 ;
    bgvalue = bgvalue + ADCRL;
    Bandgap_Voltage= READ_BANDGAP()*3/4;
    VDD_Voltage = (0x1000/bgvalue)*Bandgap_Voltage;


    while(1);

}


