/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: MS51 BOD interrupt demo code
//***********************************************************************************************************
#include "ms51_32k_iar.h"

BIT bodflag;

#pragma vector=0x43
__interrupt void BOD_ISR(void){
    PUSH_SFRS;
 
    clr_BODCON0_BOF;
    bodflag=1;

    POP_SFRS;
}

//----------------------------------------------------------------------------------------------//
void main (void)
{

  /* UART0 settting for printf function */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf (" \n\r Test start ... \n\r ");

    BOD_Open(Enable, VBOD_2_7, BOD_Reset_Disable);
    BOD_LowPower(LPBOD_Mode_3);
    BOD_Interrupt(Enable);
    ENABLE_GLOBAL_INTERRUPT;
    while(1)
    {

       if (bodflag)
       {
         printf (" \n\r  BOD interrupt! ... \n\r "); 
         bodflag = 0;
       }
  }
}


