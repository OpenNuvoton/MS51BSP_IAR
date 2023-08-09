/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define   GPIO_LED    P17
#define   GPIO_LED_QUASI_MODE  P17_QUASI_MODE
#define   GPIO_PRINTF  P06

extern BIT BIT_TMP;

extern unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr);
void _delay_(void);