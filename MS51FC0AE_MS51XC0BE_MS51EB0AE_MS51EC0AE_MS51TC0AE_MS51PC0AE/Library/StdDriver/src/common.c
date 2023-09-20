/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"

BIT BIT_TMP;
unsigned char __data TA_REG_TMP,BYTE_TMP,SFRS_TMP;

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
 * @brief       Software reset API
 * @param       None
 * @return      None 
 * @details     Call this API to excute software reset
 * @Note        Before call software reset function, please first confirm PCON define boot from APROM or LDROM
*/
void SW_Reset(void)
{
    TA = 0xAA;
    TA = 0x55;
    set_CHPCON_SWRST;
}

/**
 * @brief       Loop delay API
 * @param       None
 * @return      None
 * @details     None
 */
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

