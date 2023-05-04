/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2021 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2021                                                        
//***********************************************************************************************************


#include "MS51_16K_IAR.H"
#include "Table_Data.h"

#define EEPROM_ADDRESS          0xA0
#define I2C_WR                     0
#define I2C_RD                     1

#define LOOP_SIZE                 10

unsigned int __xdata Tx_Addr , Rx_Addr ;
unsigned int __xdata Tx_Dat = 0;
unsigned int __xdata Rx_Dat[30];
unsigned char __xdata Write_End_Flag =0, Read_End_Flag = 0;


void (*I2C_Func)(void);
#pragma vector=0x33
__interrupt void Pin_INT_ISR(void){
_push_(SFRS);
    I2C_Func();
_pop_(SFRS);    
}

/*=====  I2C master tranfer to eeprom process  ===========================*/
void I2C0_Master_Tx_Isr(void)
{
    static uint8_t addr_flag = 0;
    static uint8_t u8Count = 0;

_push_(SFRS);
    SFRS = 0;
    printf_UART("\n I2C Transmit Interrupt" );
    printf_UART("\n I2STAT = 0x%x", I2STAT);
    switch (I2STAT)
    {
       /* Bus error */
       case 0x00: set_I2CON_STO; break;
        
      /* I2C start */
       case 0x08:
            clr_I2CON_STA;
            I2DAT = (EEPROM_ADDRESS | I2C_WR);
       break;

       /* Master Transmit Address ACK (to transmit the eeprom address high byte) */
       case 0x18:
            I2DAT = HIBYTE(Tx_Addr);
            addr_flag = 1;
       break;

       /* Master Transmit Data ACK (to transmit the eeprom address low byte) */
       case 0x28:
            if(addr_flag)
            {
                I2DAT = LOBYTE(Tx_Addr);
                addr_flag = 0;
                u8Count = 0;
            }
            else
            {
                if(u8Count != 30)
                {
                    I2DAT = Table_Data[u8Count];
                    u8Count++;
                }
                else
                {
                    Write_End_Flag = 1;
                    set_I2CON_STO;
                }
            }
        break;
    }

    I2C0_SI_Check();

_pop_(SFRS);
}

/*======== I2C master read from eeprom process======================================*/
void I2C0_Master_Rx_Isr(void)
{
    static uint8_t addr_flag = 0;
    static uint8_t u8Count = 0;
_push_(SFRS);

    SFRS = 0;
    printf_UART("\n I2C Receive Interrupt" );
    printf_UART("\n I2STAT = 0x%x", I2STAT);
    switch (I2STAT)
    {
       /* Bus error */
       case 0x00: set_I2CON_STO; break;

      /* I2C start */
       case 0x08:
            clr_I2CON_STA;
            I2DAT = (EEPROM_ADDRESS | I2C_WR);
       break;

       /* Master Transmit Address ACK (to transmit the eeprom address high byte) */
       case 0x18:
            I2DAT = HIBYTE(Rx_Addr);
            addr_flag = 1;
       break;

       /* Master Transmit Data ACK  (to transmit the eeprom address low byte) */ 
       case 0x28:
            if(addr_flag)
            {
                I2DAT = LOBYTE(Rx_Addr);
                addr_flag = 0;
                u8Count = 0;
            }
            else
            {
                set_I2CON_STA;
            }
       break;  

       /* Master Repeat Start  */
       case 0x10: 
           clr_I2CON_STA;
           I2DAT = (EEPROM_ADDRESS | I2C_RD);
       break;

      /* Master Receive Address ACK  */
       case 0x40:  set_I2CON_AA; break;
       
      /* Master Receive Data ACK  */  /*I2C master read from eeprom   */
       case 0x50:
                 if(u8Count != 30)
                {
                    Rx_Dat[u8Count] = I2DAT;
                    u8Count++;
                }
                else
                {
                    Read_End_Flag = 1;
                    set_I2CON_STO;
                }
       break;
    }

    I2C0_SI_Check();

_pop_(SFRS);
}


//========================================================================================================
unsigned int I2C0_Write(unsigned int  u16I2Caddr)
{
    unsigned long count = 0;

    Write_End_Flag = 0;
    I2C_Func = I2C0_Master_Tx_Isr;
    Tx_Addr = u16I2Caddr;

    SFRS=0; printf_UART("\n Write n24LC64 data 0x%bd");
    set_I2CON_STA;             /* Start transmit */
    while(1)
    {
        count++;
        if(Write_End_Flag == 1)
        {
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}

/*========================================================================================================*/
unsigned int I2C0_Read(unsigned int *u16I2Caddr)
{
    uint32_t count = 0;
    Read_End_Flag = 0;
    I2C_Func = I2C0_Master_Rx_Isr;
    Rx_Addr = u16I2Caddr;

    SFRS=0; printf_UART("\n Receive data from n24LC64" );
    set_I2CON_STA; 
    
    while(1)
    {
        count++;
        if(Read_End_Flag == 1)
        {
            *u16I2Caddr = Rx_Dat;
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}
/*========================================================================================================*/
void Init_I2C(void)
{
    /* Set I2C GPIO */
    P13_OPENDRAIN_MODE;          /* External pull high resister in circuit */
    P14_OPENDRAIN_MODE;          /* External pull high resister in circuit */

    set_P1S_3;                   /* Setting schmit tigger mode */
    set_P1S_4;                   /* Setting schmit tigger mode */

    /* Set I2C clock rate and enable  24MHz system run 100k */
     I2C_Master_Open(24000000,100000);
    /* Set I2C Interrupt enable*/
     I2C_Interrupt(ENABLE);
     ENABLE_GLOBAL_INTERRUPT;
}

/*========================================================================================================*/
void main(void)
{
    unsigned char u8Count=0;

    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf_UART("\n I2C Master intial...");
    Init_I2C();  
    

        if(I2C0_Write(0x2000) == 1)
        {
            Timer0_Delay(24000000,50,1000);
            while (I2C0_Read(0x2000) ==0);
        }

        for (u8Count=0;u8Count<32;u8Count++)
        {
          if(Rx_Dat[u8Count] != Table_Data[u8Count])
          {
                SFRS=0; printf_UART("\n Read Byte FAIL! %x", u8Count);
          }
          else
          {
                SFRS=0; printf_UART("\n Read Byte PASS! %bd", u8Count);
          }
        }
        SFRS=0; printf_UART("\n MS51 Master W/R Finished! ");

        I2C_Close(); 

        while(1);

}

