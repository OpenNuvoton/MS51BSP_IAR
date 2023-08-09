/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"



/****************************************************************/
void Spi_Write_Byte(unsigned char u8SpiWB)
{
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    clr_SPSR_SPIF;
}
/****************************************************************/
unsigned char Spi_Read_Byte(unsigned char u8SpiWB)
{
    unsigned char u8SpiRB;
    SPDR = u8SpiWB;
    while(!(SPSR&0x80));
    u8SpiRB = SPDR;
    clr_SPSR_SPIF;
    return u8SpiRB;
}