/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"

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
    printf("\n\r Flash as EEPROM demo...Toggle P17 to Low" );

    while(GPIO_LED);

    Write_DATAFLASH_BYTE (0x1882,0x34);

    for(i=0;i<50;i++)
    {
      ArrayData[i]=i;
    }
    StructData.a=0xA1A2;
    StructData.b=0xA3A4A5A6;
    StructData.c=0xA7;

    Write_DATAFLASH_ARRAY(0x18E0,ArrayData,50);                                   //write 50 bytes need 2ms
    Write_DATAFLASH_ARRAY(0x18FE,(unsigned char *)&StructData,sizeof(StructData));//write structure 20ms

    temp = Read_APROM_BYTE((unsigned int __code *)0x18FD);
    printf("\n\r 0x18FD Value is 0x%x", temp );

    while(1);
}



