/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "ms51_32k_iar.h"
#include "sprom_code.h"

/* SPROM area address define in .xcl file */
unsigned char SPROM_FUNC(unsigned char unused)  @ "SPROM_C"
{
  GPIO_LED ^= 1;
  SPTEMP++;
  return SPTEMP;
}
