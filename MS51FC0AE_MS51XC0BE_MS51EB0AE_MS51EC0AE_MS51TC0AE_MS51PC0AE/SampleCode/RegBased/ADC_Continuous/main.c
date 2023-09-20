/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: ML51 series ADC continue mode demo code
//***********************************************************************************************************

#include "ms51_32k_iar.h"

unsigned char __xdata ResultTable[256];
unsigned char ADC_CONT_FINAL_FLAG=0;

/**
 * @brief       ADC Interrupt Subroutine
 * @param       None
 * @return      None
 * @details     Set ADC continus finished flag.
 */
#pragma vector=0x5B
__interrupt void ADC_ISR(void){
  
    PUSH_SFRS;

    clr_ADCCON0_ADCF;
    ADC_CONT_FINAL_FLAG = 1;

    POP_SFRS;
}

/**
 * @brief       ADC continus mode main loop
 * @param       None
 * @return      None
 * @details     None
 */
void main (void) 
{
    unsigned char i;
    unsigned int temp;
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf (" \n\r Test start ... \n\r ");
    
/*loop clear XRAM area . */   
    for (i=0;i<192;i++)
    {
        ResultTable[i] =0;
    }
/* ADC continus mode setting . 
   *include adc.c for ADC initial setting
*/
    ENABLE_ADC_CONTINUES_MODE;                         /* Opend ADC as continous mode */
    ENABLE_ADC_CH0;                                    /* and input from AIN0 P1.7  */
    ADC_InitialContinous(0x300,128);                   /* Define data restore in RAM start address and ADC total sample number */
    ADC_ConvertTime(ADC_CH0,2,7);                      /*  ADC sampling clock = Fsys/4, sampling timer select longest value is 7     */
    
    clr_ADCCON0_ADCF;
    ENABLE_ADC_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    
    set_ADCCON0_ADCS;                                  // Trig ADCS bit to start ADC 

/* ADC finished and print the result from XRAM. */
    while(1)
    {
      if (ADC_CONT_FINAL_FLAG)
      {
            DISABLE_ADC;
             for(i=0;i<128;i++)
            {
              temp=(ResultTable[i]<<4)+(ResultTable[i/2+128]&0x0F);
              SFRS = 0;
              printf(" \n\r  ADC No.%hd",i);
              printf(" = 0x%x ", temp);
              i++;
              temp=(ResultTable[i]<<4)+((ResultTable[(i-1)/2+128]>>4)&0x0F);
              printf(" \n\r  ADC No.%hd",i);
              printf(" = 0x%x ", temp);
              if(i==127)
              ADC_CONT_FINAL_FLAG=0;
            }
        }
      }        
}
