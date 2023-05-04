/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "MS51_16K_IAR.h"
#include "SPROM.h"

/* SPROM area address define in .xcl file */
unsigned char SPROM_FUNC(unsigned char unused)  @ "SPROM_C"
{
  P12_PUSHPULL_MODE;
  P12 ^= 1;
  SPTEMP++;
  return SPTEMP;
}
