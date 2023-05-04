/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************/
/*  File Function: MS51 IAP erase / program / read verify demo code                                        */
/***********************************************************************************************************/
#include "MS51_8K_IAR.h"

/***********************************************************************************************************/
/*  Step 1 Define APROM buffer data loop from 0 to 0x7F                                                    */
/*  Step 2 erase / erase blank check / program / read verify APROM process                                 */
/***********************************************************************************************************/
void main (void) 
{
    unsigned char i;
  
    MODIFY_HIRC(HIRC_24);
    
    for (i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
/*if P1.7 trig to low start Write APROM */ 
/*Check with Nulink ICP please always keep P1.7 to high */
    while(P17);
    Erase_APROM(0x1000,128);
    Erase_Verify_APROM(0x1000,128);
    Program_APROM(0x1000,128);
    Program_Verify_APROM(0x1000,128);

    while(1);
}