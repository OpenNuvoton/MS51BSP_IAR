/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

//***********************************************************************************************************
//  Before using this demo code, please remind below CONFOGs setting, thanks.
//                 CONFIG0.7 --> CBS=0
//                 CONFIG1 = 0xFC, because this demo code size is 2495 Byte

/*-----------------------------------------------------------------------------------------------------------*/
void main (void) 
{
    unsigned char i;
    
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf ("\n\r Test start ...\n\r");
    
    for(i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
    while (GPIO_LED);
    Erase_APROM(0x80,128);
    Erase_Verify_APROM(0x80,128);
    Program_APROM(0x80,128);
    Program_Verify_APROM(0x80,128);

    while(1);
}

