//***********************************************************************************************************
//  File Function: MS51 interrupt vector
//***********************************************************************************************************
#include "ms51_32k_iar.h"

# if 0 
/*all interrupt subroutine list */
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x03
__interrupt void INT0_ISR(void){
    PUSH_SFRS;
  
    clr_TCON_IE0;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){
    PUSH_SFRS;
  
    clr_TCON_TF0;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x13
__interrupt void INT1_ISR(void){
    PUSH_SFRS;
  
    clr_TCON_IE1;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x1B
__interrupt void Timer1_ISR(void){
    PUSH_SFRS;
  
    clr_TCON_TF1;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x23
__interrupt void UART0_ISR(void){
    PUSH_SFRS;
  
    clr_SCON_RI;
    clr_SCON_TI;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x2B
__interrupt void Timer2_ISR(void){
    PUSH_SFRS;
  
    clr_T2CON_TF2;

    POP_SFRS;
}

//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x3B
__interrupt void Pin_INT_ISR(void){
    PUSH_SFRS;
  
    PIF = 0;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x43
__interrupt void BOD_ISR(void){
    PUSH_SFRS;
  
    clr_BODCON0_BOF;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x4B
__interrupt void SPI_ISR(void){
    PUSH_SFRS;
  
    clr_BODCON0_BOF;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x53
__interrupt void WDT_ISR (void){
    PUSH_SFRS;
  
    clr_WDCON_WDTF;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x5B
__interrupt void ADC_ISR (void){
    PUSH_SFRS;
  
    clr_ADCCON0_ADCF;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x63
__interrupt void Capture_ISR (void){
    PUSH_SFRS;
  
    clr_CAPCON0_CAPF0;
    clr_CAPCON0_CAPF1;
    clr_CAPCON0_CAPF2;
}
#pragma vector=0x6B
__interrupt void PWM_ISR (void){
    PUSH_SFRS;
  


    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x73
__interrupt void PWM_Brake_ISR(void){
    PUSH_SFRS;
  
    clr_PWM0FBD_FBF;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------

#pragma vector=0x83
__interrupt void Timer3_ISR(void){
    PUSH_SFRS;
  
    clr_T3CON_TF3;

    POP_SFRS;
}
//-----------------------------------------------------------------------------------------------------------
#pragma vector=0x8B
__interrupt void WKT_ISR(void){
    PUSH_SFRS;
  
    clr_WKCON_WKTF;

    POP_SFRS;
}

#endif 


  /**
  * @brief This API configures Interrupt level
  * @param[in] u8InterruptSource . Valid values are the interrupt name:
  *                       - \ref INT_INT0      :
  *                       - \ref INT_BOD        :
  *                       - \ref INT_WDT        :
  *                       - \ref INT_Timer0     :
  *                       - \ref INT_I2C0       :
  *                       - \ref INT_ADC        :
  *                       - \ref INT_INT1       :
  *                       - \ref INT_PIT        :
  *                       - \ref INT_Timer1     :
  *                       - \ref INT_UART0      :
  *                       - \ref INT_PWM0_Brake
  *                       - \ref INT_SPI0       :
  *                       - \ref INT_Timer2     :
  *                       - \ref INT_Capture    :
  *                       - \ref INT_PWM0       : 
  *                       - \ref INT_Timer3     :
  *                       - \ref INT_WKT        :
  * @note      u8u8InterruptPriorityLevel.Valid values are the interrupt level number:
  *                       - \ref 0~3            :
  * @exmaple : Set_Interrupt_Priority_Level(INT_ADC, 1);
  */
void Set_Interrupt_Priority_Level( unsigned char u8InterruptSource, unsigned char u8u8InterruptPriorityLevel)
{
   switch (u8InterruptSource)
   {
        case INT_INT0        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX0; clr_IPH_PX0H; break;
            case 1:  clr_IP_PX0; set_IPH_PX0H; break;
            case 2:  set_IP_PX0; clr_IPH_PX0H; break;
            case 3:  clr_IP_PX0; set_IPH_PX0H; break;
          }
        case INT_BOD          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PBOD; clr_IPH_PBODH; break;
            case 1:  clr_IP_PBOD; set_IPH_PBODH; break;
            case 2:  set_IP_PBOD; clr_IPH_PBODH; break;
            case 3:  set_IP_PBOD; set_IPH_PBODH; break;
          }
        case INT_WDT           :
               switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 1:  clr_EIP_PWDT; set_EIPH_PWDTH; break;
            case 2:  set_EIP_PWDT; clr_EIPH_PWDTH; break;
            case 3:  set_EIP_PWDT; set_EIPH_PWDTH; break;
          }        
        case INT_Timer0        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT0; clr_IPH_PT0H; break;
            case 1:  clr_IP_PT0; set_IPH_PT0H; break;
            case 2:  set_IP_PT0; clr_IPH_PT0H; break;
            case 3:  set_IP_PT0; set_IPH_PT0H; break;
          }
        case INT_I2C0          :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 1:  clr_EIP_PI2C; set_EIPH_PI2CH; break;
            case 2:  set_EIP_PI2C; clr_EIPH_PI2CH; break;
            case 3:  set_EIP_PI2C; set_EIPH_PI2CH; break;
          }
        case INT_ADC           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PADC; clr_IPH_PADCH; break;
            case 1:  clr_IP_PADC; set_IPH_PADCH; break;
            case 2:  set_IP_PADC; clr_IPH_PADCH; break;
            case 3:  set_IP_PADC; set_IPH_PADCH; break;
          }        
        case INT_INT1        :
          switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PX1; clr_IPH_PX1H; break;
            case 1:  clr_IP_PX1; set_IPH_PX1H; break;
            case 2:  set_IP_PX1; clr_IPH_PX1H; break;
            case 3:  set_IP_PX1; set_IPH_PX1H; break;
          }
        case INT_PIT           :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_EIP_PPI; clr_EIPH_PPIH; break;
            case 1:  clr_EIP_PPI; set_EIPH_PPIH; break;
            case 2:  set_EIP_PPI; clr_EIPH_PPIH; break;
            case 3:  set_EIP_PPI; set_EIPH_PPIH; break;
          }        
        case INT_Timer1        :
                switch (u8u8InterruptPriorityLevel)
          {
            case 0:  clr_IP_PT1; clr_IPH_PT1H; break;
            case 1:  clr_IP_PT1; set_IPH_PT1H; break;
            case 2:  set_IP_PT1; clr_IPH_PT1H; break;
            case 3:  set_IP_PT1; set_IPH_PT1H; break;
          }
        case INT_UART0         :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_IP_PS; clr_IPH_PSH; break;
            case 1:  clr_IP_PS; set_IPH_PSH; break;
            case 2:  set_IP_PS; clr_IPH_PSH; break;
            case 3:  set_IP_PS; set_IPH_PSH; break;
          }        
        case INT_PWM0_Brake :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PFB; clr_EIPH_PFBH; break;
            case 1:  clr_EIP_PFB; set_EIPH_PFBH; break;
            case 2:  set_EIP_PFB; clr_EIPH_PFBH; break;
            case 3:  set_EIP_PFB; set_EIPH_PFBH; break;
          }
        case INT_SPI0          :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 1:  clr_EIP_PSPI; set_EIPH_PSPIH; break;
            case 2:  set_EIP_PSPI; clr_EIPH_PSPIH; break;
            case 3:  set_EIP_PSPI; set_EIPH_PSPIH; break;
          }        
        case INT_Timer2        :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PT2; clr_EIPH_PT2H; break;
            case 1:  clr_EIP_PT2; set_EIPH_PT2H; break;
            case 2:  set_EIP_PT2; clr_EIPH_PT2H; break;
            case 3:  set_EIP_PT2; set_EIPH_PT2H; break;
          }         
        case INT_Capture       :
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 1:  clr_EIP_PCAP; set_EIPH_PCAPH; break;
            case 2:  set_EIP_PCAP; clr_EIPH_PCAPH; break;
            case 3:  set_EIP_PCAP; set_EIPH_PCAPH; break;
          }
        case INT_PWM0          :                          
              switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 1:  clr_EIP_PPWM; set_EIPH_PPWMH; break;
            case 2:  set_EIP_PPWM; clr_EIPH_PPWMH; break;
            case 3:  set_EIP_PPWM; set_EIPH_PPWMH; break;
          }
        case INT_UART1         :
             switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 1:  clr_EIP1_PS_1; set_EIPH1_PSH_1; break;
            case 2:  set_EIP1_PS_1; clr_EIPH1_PSH_1; break;
            case 3:  set_EIP1_PS_1; set_EIPH1_PSH_1; break;
          }        
        case INT_Timer3        :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 1:  clr_EIP1_PT3; set_EIPH1_PT3H; break;
            case 2:  set_EIP1_PT3; clr_EIPH1_PT3H; break;
            case 3:  set_EIP1_PT3; set_EIPH1_PT3H; break;
          } 
        case INT_WKT           :
            switch (u8u8InterruptPriorityLevel)
          {          
            case 0:  clr_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 1:  clr_EIP1_PWKT; set_EIPH1_PWKTH; break;
            case 2:  set_EIP1_PWKT; clr_EIPH1_PWKTH; break;
            case 3:  set_EIP1_PWKT; set_EIPH1_PWKTH; break;
          }
        break;
   }
 }
