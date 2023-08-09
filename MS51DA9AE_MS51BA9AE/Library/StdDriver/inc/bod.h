/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#define   VBOD_2_2           0x30
#define   VBOD_2_7           0x20
#define   VBOD_3_7           0x10
#define   VBOD_4_4           0x00

#define   BOD_Reset_Enable   0x04
#define   BOD_Reset_Disable  0


void BOD_Open(unsigned char u8bodstatus, unsigned char u8bodlevel, unsigned char u8bodresetstatus);
void BOD_Interrupt (unsigned char u8bodINTstatus);
