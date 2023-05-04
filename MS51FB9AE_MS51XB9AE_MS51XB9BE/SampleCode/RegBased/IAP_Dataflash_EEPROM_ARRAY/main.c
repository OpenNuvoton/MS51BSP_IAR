/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "MS51_16K_IAR.H"

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
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART("\n Flash as EEPROM demo...Toggle P14 to Low" );  
  /*loop here while P46 = 1; */  
    P14_QUASI_MODE;
    while(P14);


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
    printf_UART("\n 0x18FD Value is 0x%x", temp );
    
    while(1);
}



