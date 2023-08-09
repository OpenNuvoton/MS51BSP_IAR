/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_16k_iar.h"

struct
{
  unsigned int a;
  unsigned long b;
  unsigned char  c;
  
}StructData;

unsigned char ArrayData[50];
unsigned char i;

/**
 * @brief       IAP program dataflash as EEPROM
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value,
 */

void main (void) 
{
    unsigned char temp;
      
    MODIFY_HIRC(HIRC_24);
    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf_24M_115200();
    printf(" \n\r Flash as EEPROM demo...Toggle P12 to Low  \n\r " ); 
    
  /*loop here while P12 = 1; */  
    while(GPIO_LED);

/** IAP program APROM as EEPROM way
   * include eeprom.c in Library       */ 
 
    Write_DATAFLASH_BYTE (0x1882,0x34);

    for(i=0;i<50;i++)
    {
      ArrayData[i]=i;
    }

    StructData.a=0x5152;
    StructData.b=0x53545556;
    StructData.c=0x57;
  
    Write_DATAFLASH_ARRAY(0x18E0,ArrayData,50);//write 50 bytes
    Write_DATAFLASH_ARRAY(0x18FE,(unsigned char *)&StructData,sizeof(StructData));//write structure

    temp = Read_APROM_BYTE((unsigned int __code *)0x18FD);
    printf(" \n\r  0x18FD Value is 0x%x", temp );
    
    while(1);
}



