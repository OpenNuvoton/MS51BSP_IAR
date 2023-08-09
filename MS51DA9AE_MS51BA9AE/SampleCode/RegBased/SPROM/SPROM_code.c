/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"
#include "sprom.h"

/* SPROM area address define in .xcl file */
unsigned char SPROM_FUNC(unsigned char unused)  @ "SPROM_C"
{
  GPIO_LED ^= 1;
  SPTEMP++;
  return SPTEMP;
}
