/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo code                                                  */
//**********************************************************************************************************/

#include "MS51_8K_IAR.h"


//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
double  Bandgap_Voltage,VDD_Voltage;      //please always use "double" mode for this

void READ_BANDGAP()
{
    unsigned int Bandgap_Value;
    unsigned char BandgapHigh,BandgapLow;

    set_CHPCON_IAPEN;
    IAPCN = READ_UID;
    IAPAL = 0x0d;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapLow = IAPFD;
    BandgapLow = BandgapLow&0x0F;
    IAPAL = 0x0C;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    BandgapHigh = IAPFD;
    Bandgap_Value = (BandgapHigh<<4)+BandgapLow;
    Bandgap_Voltage= Bandgap_Value*3/4;
    clr_CHPCON_IAPEN;
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
   unsigned int bgvalue;
   unsigned  char  ADCdataH, ADCdataL;
   
   MODIFY_HIRC(HIRC_24);

/*Read bandgap value */
    READ_BANDGAP();
/* ADC Low speed initial*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                                
    while(ADCF == 0);
    ADCdataH = ADCRH;
    ADCdataL = ADCRL;
/* to convert VDD value */
    bgvalue = (ADCdataH<<4) + ADCdataL;

    VDD_Voltage = (double)0x1000/bgvalue*Bandgap_Voltage;
    while(1);

}


