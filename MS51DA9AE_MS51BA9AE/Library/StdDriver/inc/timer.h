/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define DIV1      1
#define DIV2      2
#define DIV4      4
#define DIV8      8
#define DIV16     16
#define DIV32     32
#define DIV64     64
#define DIV128    128

void Timer0_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer0_CounterClear(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer0_Interrupt_Disable(void);
void Timer1_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer1_CounterClear(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer1_Interrupt_Disable(void);
void Timer2_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer2_CounterClear(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer2_Interrupt_Disable(void);
void Timer3_AutoReload_Interrupt_Initial(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer3_CounterClear(unsigned char u8SYSCLK, unsigned long u32DLYUnit);
void Timer3_Interrupt_Disable(void);
