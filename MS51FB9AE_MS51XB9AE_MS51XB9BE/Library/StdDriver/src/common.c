/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "MS51_16K_IAR.H"

BIT BIT_TMP;
/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr)
{
    unsigned char rdata;
    rdata = *u16_addr >> 8;
    return rdata;
}

/**
 * @brief       Loop delay  
 * @param       None
 * @return      None
 * @details     None
**/
void _delay_(void)
{
  unsigned char ui,uj;
    for (uj=0;uj<0x1A;uj++)
    {
       for (ui=0;ui<0xff;ui++)
       {
          _nop_();
       }
    }
}  