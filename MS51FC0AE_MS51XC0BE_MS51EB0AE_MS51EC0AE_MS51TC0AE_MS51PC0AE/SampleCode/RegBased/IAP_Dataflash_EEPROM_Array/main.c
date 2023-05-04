/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "MS51_32K_IAR.h"

struct
{
    unsigned int a;
    unsigned long b;
    unsigned char  c;

} StructData;

unsigned char ArrayData[50];
unsigned char i;

/**
 * @brief       IAP program dataflash as EEPROM
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value,
 */

void main(void)
{
    unsigned char temp;
    
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART("\n Flash as EEPROM demo...Toggle P01 to Low" );

    P01_QUASI_MODE;
    while (P01);

    /** IAP program APROM as EEPROM way * include eeprom.c in Library       */

    Write_DATAFLASH_BYTE(0x3882, 0x34);

    for (i = 0; i < 50; i++)
    {
        ArrayData[i] = i;
    }

    StructData.a = 0x5152;
    StructData.b = 0x53545556;
    StructData.c = 0x57;

    Write_DATAFLASH_ARRAY(0x38E0, ArrayData, 50); //write 50 bytes
    Write_DATAFLASH_ARRAY(0x38FE, (unsigned char *)&StructData, sizeof(StructData)); //write structure

    /*call read byte */
    temp = Read_APROM_BYTE((unsigned int __code *)0x38FD);
    printf_UART("\n Data flash 0x38FD = 0x%x", temp);
    
    while (1);
}



