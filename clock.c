/***************************************************************************
  FileName:        clock.c
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* CLOCK configuration- core + Peripheral                                  */
/*-------------------------------------------------------------------------*/
//      
//    core clock : 4 MHz
//    
//***************************************************************************
#include <saml10e16a.h>
#include "clock.h"

/*if you need a faster internal clock use this function*/
//void ClockCore_set(void){
///*set the OSC16M value to 16MHz*/
//OSCCTRL->OSC16MCTRL.bit.FSEL = 0b11; 
//while(!OSCCTRL->STATUS.bit.OSC16MRDY);
//}

void Clock_EIC_init(void){
/*Start EIC Clock configuration*/
/*PCHCTRL3 --> GEN0 --> 0x0   / connect EIC to Generator nr 0*/
GCLK->PCHCTRL[3].bit.GEN = GCLK_PCHCTRL_GEN_GCLK0_Val;
/*PCHCTRL3 --> CHEN --> 1  / switch on canal for clock EIC*/
GCLK->PCHCTRL[3].bit.CHEN = 1;

}

void Clock_Sercom_init(void){
/*Start SERCOM1 Clock configuration*/
/*PCHCTRL10 --> GEN --> 0x0   / connect SERCOM1 and SERCOM0 Slow to Generator nr 0*/
GCLK->PCHCTRL[10].bit.GEN = GCLK_PCHCTRL_GEN_GCLK0_Val;
/*PCHCTRL10 --> CHEN --> 1  / switch on canal for clock SERCOM1 and SERCOM0 Slow*/
GCLK->PCHCTRL[10].bit.CHEN = 1;
/*PCHCTRL12 --> GEN --> 0x0   / connect SERCOM1 Core to Generator nr 0*/
GCLK->PCHCTRL[12].bit.GEN = GCLK_PCHCTRL_GEN_GCLK0_Val;
/*PCHCTRL12 --> CHEN --> 1  / switch on canal for clock SERCOM1 Core*/
GCLK->PCHCTRL[12].bit.CHEN = 1;

/*Start SERCOM0 Clock configuration*/
/*PCHCTRL11 --> GEN --> 0x0   / connect SERCOM0 Core to Generator nr 0*/
GCLK->PCHCTRL[11].bit.GEN = GCLK_PCHCTRL_GEN_GCLK0_Val;
/*PCHCTRL11 --> CHEN --> 1  / switch on canal for clock SERCOM0 Core*/
GCLK->PCHCTRL[11].bit.CHEN = 1;
}

