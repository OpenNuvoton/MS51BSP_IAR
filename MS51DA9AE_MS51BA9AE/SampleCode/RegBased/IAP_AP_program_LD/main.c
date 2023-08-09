/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


void main (void) 
{
    unsigned char i;
    
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
  
/*Modify CONFIG Enable LDROM, LDROM size is 2k*/
    Modify_CONFIG(0xEF,0xFD,0xFF,0xFF,0xFF);

/* IAP data buffer size is 128 since each page of MS51 is 128 byte*/
    for(i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
		
/* Only when P1.7 to low to program LDROM process*/
    while (GPIO_LED);
    Erase_LDROM(0,128);
    Erase_Verify_LDROM(0,128);
    Program_LDROM(0,128);
    Program_Verify_LDROM(0,128);

    while(1);

}

