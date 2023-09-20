/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_32k_iar.h"


BIT PRINTFG,uart0_receive_flag,uart1_receive_flag;
unsigned char uart0_receive_data,uart1_receive_data;

/**
 * @brief       UART0 interrupt vector demo
 * @param       None
 * @return      None
 * @details     UART0 store received data.
 */
#if 0
#pragma vector=0x23
__interrupt void UART0_ISR(void){
  
    PUSH_SFRS;
    
      if (RI)
    {   
      uart0_receive_flag = 1;
      uart0_receive_data = SBUF;
      clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if  (TI)
    {
      if(!PRINTFG)
      {
          clr_SCON_TI;
      }
    }

    POP_SFRS;
}
#endif 

/**
 * @brief       UART1 interrupt vector demo
 * @param       None
 * @return      None
 * @details     UART1 store received data.
 */
#if 0
#pragma vector=0x7B
__interrupt void SerialPort1_ISR(void){
    PUSH_SFRS;
  
    if (RI_1==1) 
    {                                       
        clr_SCON_1_RI_1;                            
       uart1_receive_data = SBUF_1;
        uart1_receive_flag =1;
    }
    if(TI_1==1)
    {
       if(!PRINTFG)
      {
          clr_SCON_1_TI_1;                            
      }  
    }

    POP_SFRS;
}
#endif 
/*MS51 new version buadrate */
void UART_Open(unsigned long u32SysClock, unsigned char u8UARTPort,unsigned long u32Baudrate)
{
  switch(u8UARTPort)
  {
    case UART0_Timer1:
          P06_QUASI_MODE;         //Setting UART pin as Quasi mode for transmit
          SCON = 0x50;            //UART0 Mode1,REN=1,TI=1
          TMOD |= 0x20;           //Timer1 Mode1
          set_PCON_SMOD;          //UART0 Double Rate Enable
          set_CKCON_T1M;
          clr_T3CON_BRCK;          //Serial port 0 baud rate clock source = Timer1
          TH1 = 256 - (u32SysClock/16/u32Baudrate);
          set_TCON_TR1;
          ENABLE_UART0_INTERRUPT;
      break;
      
      case UART0_Timer3:
          P06_QUASI_MODE;    //Setting UART pin as Quasi mode for transmit
          SCON = 0x50;          //UART0 Mode1,REN=1,TI=1
          set_PCON_SMOD;        //UART0 Double Rate Enable
          T3CON &= 0xF8;        //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
          set_T3CON_BRCK;        //UART0 baud rate clock source = Timer3
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          set_T3CON_TR3;         //Trigger Timer3
          ENABLE_UART0_INTERRUPT;
      break;
      
      case UART1_Timer3:
          P16_QUASI_MODE;       //Setting UART pin as Quasi mode for transmit
          P02_INPUT_MODE;       //Setting RXD_1 pin as Input mode for transmit   
          SCON_1 = 0x50;        //UART1 Mode1,REN_1=1,TI_1=1
          T3CON = 0x80;         //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));  
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));     
          set_T3CON_TR3;             //Trigger Timer3
          ENABLE_UART1_INTERRUPT;
      break;
  }

}

unsigned char Receive_Data(unsigned char UARTPort)
{
    UINT8 c;
    switch (UARTPort)
    {
      case UART0:
        while (!RI);
        c = SBUF;
        RI = 0;
      break;
      case UART1:
        while (!RI_1);
        c = SBUF_1;
        RI_1 = 0;
      break;
    }
    return (c);
}

void UART_Send_Data(unsigned char UARTPort, unsigned char c)
{
    switch (UARTPort)
    {
      case UART0:
        TI = 0 ;
        SBUF = c;
        while (!TI);
      break;
      case UART1:
        TI_1 = 0;
        SBUF_1 = c;
        while (!TI_1);
      break;
    }
}


/**
 * @brief       UART printf initial @ 24M Fsys baud rate 115200
 * @param       None
 * @return      None
 * @details     None
 */
void Enable_UART0_VCOM_printf_24M_115200(void)
{
    P06_QUASI_MODE;
    UART_Open(24000000,UART0_Timer1,115200);
    ENABLE_UART0_PRINTF;
    DISABLE_UART0_INTERRUPT;
}
void printf_UART(unsigned char *str, ...);

void printInteger(unsigned long u32Temp)
{
    unsigned char print_buf[16];
    unsigned long i = 15, j;

    *(print_buf + i) = '\0';
    j = u32Temp >> 31;
    if(j)
        u32Temp = ~u32Temp + 1;
    do
    {
        i--;
        *(print_buf + i) = '0' + u32Temp % 10;
        u32Temp = u32Temp / 10;
    }
    while(u32Temp != 0);
    if(j)
    {
        i--;
        *(print_buf + i) = '-';
    }
    printf_UART(print_buf + i);
}
void printHex(unsigned long u32Temp)
{
    unsigned char print_buf[16];
    unsigned long i = 15;
    unsigned long temp;

    *(print_buf + i) = '\0';
    do
    {
        i--;
        temp = u32Temp % 16;
        if(temp < 10)
            *(print_buf + i) = '0' + temp;
        else
            *(print_buf + i) = 'a' + (temp - 10) ;
        u32Temp = u32Temp / 16;
    }
    while(u32Temp != 0);
    printf_UART(print_buf + i);
}
void printf_UART(unsigned char *str, ...)
{
    va_list args;
    va_start(args, str);
    while(*str != '\0')
    {
        if(*str == '%')
        {
            str++;
            if(*str == '\0') return;
            if(*str == 'd')
            {
                str++;
                printInteger(va_arg(args, int));
            }
            else if(*str == 'x')
            {
                str++;
                printHex(va_arg(args, int));
            }
        }
        UART_Send_Data(UART0,*str++);
    }
}
