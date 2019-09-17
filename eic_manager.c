/***************************************************************************
  FileName:        eic_manager.c
  Processor:       ATSAML10E16A
  IDE :            SEGGER ver 4.20
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* EIC module configuration                                                */
/*-------------------------------------------------------------------------*/
#include <saml10e16a.h>
#include <stdio.h>
#include <stdlib.h>


void EIC_Manager_init(void){
REG_EIC_CONFIG0 |= EIC_CONFIG_SENSE3_FALL; //Detect a change from H to L
REG_EIC_CTRLA |= EIC_CTRLA_ENABLE; // EIC Module Enbable
while (EIC->SYNCBUSY.bit.ENABLE) { }; //Wait for Synchro Clock
/* Enable interrupt on EXTINT[3] */
EIC->INTENSET.reg = (EIC_INTENSET_EXTINT((1<<3))); //Enable Interrupt from EXTINT[3]
//NVIC_EnableIRQ(EIC_3_IRQn); //see EIC3_Start()

}

void EIC3_Start(void){
//NVIC_SetPriority(EIC_3_IRQn, 11) ;
NVIC_EnableIRQ(EIC_3_IRQn);
}

void EIC3_Stop(void){
NVIC_DisableIRQ(EIC_3_IRQn);
}

