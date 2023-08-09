/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ms51_8k_iar.h"


//***********************************************************************************************************
//  File Function: MS51 I2C demo code, Slave Address of 24LC64 = 0xA0
//
//   ____________           ______________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  | MS51(M)    |          |   24LC64(S) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  Microchip I2C EEPROM 24xx64 (64K Bit) is used as the slave device.  
//  The page size are 32Byte. Total are 256 page.
//  If verification passes, Port3 will show 0x78. If there is any failure
//  occured during the progress, Port3 will show 0x00.
//***********************************************************************************************************

#define I2C_CLOCK               2

#define EEPROM_SLA              0xA0
#define EEPROM_WR               0
#define EEPROM_RD               1

#define EEPROM_PAGE_SIZE        32
#define PAGE_NUMBER             4

#define ERROR_CODE              0x78
#define TEST_OK                 0x00

#define TIMEROUT                30000

BIT I2C_Reset_Flag,I2C_Fail_Flag;

/**
  * @brief  Timer0 time out interrupt  
  * @note   When into timer0 intterupt means I2C trans error 
*/
#pragma vector=0x0B                             /* interrupt 1 */
__interrupt void Timer0_ISR(void){
_push_(SFRS);
       I2C_Reset_Flag = 1;
/* following clear flag for next interrupt */
      clr_TCON_TF0;

_pop_(SFRS);
}

//========================================================================================================
void Init_I2C(void)
{
    P03_OPENDRAIN_MODE;     /*I2C_SCL*/
    P04_OPENDRAIN_MODE;     /*I2C_SDA*/
    set_P0S_3;
    set_P0S_4;
    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK; 

    /* Enable I2C */
    set_I2CON_I2CEN;
}
//========================================================================================================
void I2C_SI_Check(void)
{
    if (I2STAT == 0x00)
    {
        I2C_Reset_Flag = 1;
        set_I2CON_STO;
        clr_I2CON_SI;
        if(I2CON&SET_BIT3)
        {
            clr_I2CON_I2CEN;
            set_I2CON_I2CEN;
            clr_I2CON_SI;
            clr_I2CON_I2CEN;    
        }   
    }  
}

void One_Page_Read(uint8_t u8PageNumber,uint8_t u8DAT)
{
    uint8_t  u8Count;
    uint16_t u16Address;

    u16Address = (uint16_t)u8PageNumber*32;

    /* Step1 */
    set_I2CON_STA;                                /* Send Start bit to I2C EEPROM */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3))
    {
      if (I2C_Reset_Flag)
        goto Read_Error_Stop;
    }
    if (I2STAT != 0x08)                           /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }
    Timer0_CounterClear(8,TIMEROUT);
    
    /* Step2 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_I2CON_STA;                                /* Clear STA and Keep SI value in I2CON */    
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send I2C EEPROM's High Byte Address */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send I2C EEPROM's Low Byte Address */
    clr_I2CON_SI;
   while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */             
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }

    /* Step5 */
    set_I2CON_STA;                                /* Repeated START */
    clr_I2CON_SI; 
   while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }

    /* Step6 */
    clr_I2CON_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }

    /* Step7 */                             /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <EEPROM_PAGE_SIZE; u8Count++)
    {
        set_I2CON_AA;                             /* Set Assert Acknowledge Control Bit */
        clr_I2CON_SI;
       while (!(I2CON&SET_BIT3));
        if (I2STAT != 0x50)                 /* 0x50:Data byte has been received; NOT ACK has been returned */              
        {
            I2C_Reset_Flag = 1;
            goto Read_Error_Stop;
        }
       
        if (I2DAT != u8DAT)                 /* Send the Data to EEPROM */    
        {
            I2C_Reset_Flag = 1;
            goto Read_Error_Stop;
        }
        u8DAT = ~u8DAT; 
    }

    /* Step8 */
    clr_I2CON_AA;                                 /* Send a NACK to disconnect 24xx64 */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));
    if (I2STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        I2C_Reset_Flag = 1;
        goto Read_Error_Stop;
    }
    
  /* Step9 */    
    clr_I2CON_SI;
    set_I2CON_STO;
    while (I2CON&SET_BIT4)                        /* Check STOP signal */
    {
      I2C_SI_Check();
      if (I2C_Reset_Flag)
        goto Read_Error_Stop;
    }
    
Read_Error_Stop: 
    if (I2C_Reset_Flag)
    {
        I2C_SI_Check();
        I2C_Reset_Flag = 0;
        I2C_Fail_Flag = 1;
        Timer0_Interrupt_Disable();
        printf("\n\r I2C Read error!");
    }
}
//========================================================================================================
void One_Page_Write(uint8_t u8PageNumber,uint8_t u8DAT)
{
    uint8_t  u8Count;
    uint16_t u16Address;

    u16Address = (uint16_t)u8PageNumber*32;

    /* Step1 */
    set_I2CON_STA;                          /* Send Start bit to I2C EEPROM */         
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3))               /*Wait SI to be 1 */
    {
      if (I2C_Reset_Flag)
        goto Write_Error_Stop;
    }
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
        goto Write_Error_Stop;
    }
    
    /* Step2 */
    clr_I2CON_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */             
    {
        I2C_Reset_Flag = 1;
        goto Write_Error_Stop;
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send EEPROM's High Byte Address */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
        goto Write_Error_Stop;
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send EEPROM's Low Byte Address */
    clr_I2CON_SI;
    while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
        goto Write_Error_Stop;
    }

    /* Step5 */
                                            /* Write data to I2C EEPROM */
    for (u8Count = 0; u8Count < EEPROM_PAGE_SIZE; u8Count++)
    {
        I2DAT = u8DAT;                      /* Send data to EEPROM */
        clr_I2CON_SI;
        while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
        if (I2STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
        {
            I2C_Reset_Flag = 1;
            goto Write_Error_Stop;
        }   
        u8DAT = ~u8DAT;        
    }
                                            //After STOP condition, a inner EEPROM timed-write-cycle 
                                            //will occure and EEPROM will not response to outside command
                                            /* 0x18: SLA+W has been transmitted; ACK has been received */
    /* Step6 */
    do
    {
        set_I2CON_STO;                            /* Set I2C STOP Control Bit */
        clr_I2CON_SI;
        while (I2CON&SET_BIT4)                        /* Check STOP signal */
        {
          I2C_SI_Check();
          if (I2C_Reset_Flag)
            goto Write_Error_Stop;
        }
       
        set_I2CON_STA;                            /* Check if no ACK is returned by EEPROM, it is under timed-write cycle */
        clr_I2CON_SI;
        while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
        if (I2STAT != 0x08)                 /* 0x08:  A START condition has been transmitted*/
        {
            I2C_Reset_Flag = 1;
            goto Write_Error_Stop;
        }
         
        clr_I2CON_STA;                            /* Clear STA and Keep SI value in I2CON */
        I2DAT = (EEPROM_SLA | EEPROM_WR);         /* Send (SLA+W) to EEPROM */
        clr_I2CON_SI;
        while (!(I2CON&SET_BIT3));               /*Wait SI to be 1 */
    }while(I2STAT != 0x18);

    /* Step7 */
    set_I2CON_STO;                                /* Set STOP Bit to I2C EEPROM */
    clr_I2CON_SI;
     while (I2CON&SET_BIT4)                        /* Check STOP signal */
    {
      I2C_SI_Check();
      if (I2C_Reset_Flag)
        goto Write_Error_Stop;
    }
    
Write_Error_Stop: 
    if (I2C_Reset_Flag)
    {
        I2C_SI_Check();
        I2C_Reset_Flag  = 0;
        I2C_Fail_Flag  = 1;
        Timer0_Interrupt_Disable();
        printf("\n\r I2C writer error!");
    }
}
//========================================================================================================
void main(void)
{


/* Initial UART0 for printf */
    MODIFY_HIRC(HIRC_24);
    Enable_UART0_VCOM_printf_24M_115200();
    printf("\n\r I2C Flash Write/Read Test start...");
    /* Initial I2C function */
    Init_I2C();                                 //initial I2C circuit
    /* Initial trans time out function */
    Timer0_AutoReload_Interrupt_Initial(8,TIMEROUT);
    ENABLE_TIMER0_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    
    /* page0 R/W */
    printf("\n\r Page0 (0x55,0xAA...)...");
    One_Page_Write(0,0x55);                     //page0, write 0x55,0xAA,........
    if (I2C_Fail_Flag)
      goto ENDINFO;
    One_Page_Read (0,0x55);                     //page0, read  0x55,0xAA,........
    
    /* page1 R/W */
    One_Page_Write(1,0x00);                     //page1, write 0x00,0xFF,........
    One_Page_Read (1,0x00);                     //page1, read  0x00,0xFF,........

    /* page255 R/W */
    printf("\n\r Page255  (0x0F,0xF0...)...");
    One_Page_Write(255,0x0F);                   //page255, write 0x0F,0xF0,........
    One_Page_Read (255,0x0F);                   //page255, read  0x0F,0xF0,........

ENDINFO:
    /* ==== Test Pass ==== */
    if (!I2C_Fail_Flag)
    {
       printf("\n\r Test pass !");
    }
    else
    {
      printf("\n\r Test fail stop !");
    }
    while (1);

/* =================== */
}

