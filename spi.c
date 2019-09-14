/***************************************************************************
  FileName:        spi.c
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* SPI configuration + SPI send/receive function                                   */
/*-------------------------------------------------------------------------*/
//      
//    Reqired SPI connections :
//     Signal SI4463 ---> MCU ATSAML10E16
//     MOSI                     --> PA10
//     MISO                     --> PA09
//     SCK                      --> PA11
//     
//***************************************************************************
#include <saml10e16a.h>
#include "spi.h"

/*SPI on SERCOM1*/
void SPI_Sercom1_init(void){
/*CTRLA --> ENABLE --> 0 / switch off SPI */
SERCOM1->SPI.CTRLA.bit.ENABLE = 0;
/*wait for synchro*/
while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE == 1);
/*CTRLA --> MODE --> 0x3  / switch on SPI MASTER for SERCOM*/
SERCOM1->SPI.CTRLA.bit.MODE = 0x3;
/*CTRLB --> RXENABLE --> 1 / switch on RX, use MISO*/
SERCOM1->SPI.CTRLB.bit.RXEN = 1;
/*wait for synchro*/
while(SERCOM1->SPI.SYNCBUSY.bit.CTRLB);
/*CTRLA --> DIPO -->  0x1 / in mode MASTER allocate PAD[1] to the MISO*/
SERCOM1->SPI.CTRLA.bit.DIPO = 0x1; 
/*CTRLA --> DOPO -->  0x1 / in mode MASTER allocate PAD[2] to the MOSI and PAD[3] to the CLK*/
SERCOM1->SPI.CTRLA.bit.DOPO = 0x1;
/*BAUD --> BAUD --> 0 / set Baud Generator (0-255)*/
SERCOM1->SPI.BAUD.reg = 0; //for Baud = 0 --> f max = F Core / 2
/*Interrupt flag TXC on and RXC on and DRE on*/
SERCOM1->SPI.INTENSET.bit.TXC = 1;
SERCOM1->SPI.INTENSET.bit.RXC = 1;
SERCOM1->SPI.INTENSET.bit.DRE = 1;
/*CTRLA --> ENABLE --> 1 / switch on SPI*/
SERCOM1->SPI.CTRLA.bit.ENABLE = 1;
/*wait for synchro*/
while(SERCOM1->SPI.SYNCBUSY.bit.ENABLE == 1);
/*End  SPI configuration*/
}

uint8_t SPI_Exchange8bit(uint8_t data)
{  
    //wait for data register to be empty
    while(!SERCOM1->SPI.INTFLAG.bit.DRE);
    /*send data*/
    SERCOM1->SPI.DATA.reg = data; //send data
     /*wait for transfer complete*/
    while(!SERCOM1->SPI.INTFLAG.bit.RXC);
    //return received data
    data = REG_SERCOM1_SPI_DATA;
    return data ;
       
}

/*SPI on SERCOM0*/
void SPI_Sercom0_init(void){
/*CTRLA --> ENABLE --> 0 / switch off SPI */
SERCOM0->SPI.CTRLA.bit.ENABLE = 0;
/*wait for synchro*/
while(SERCOM0->SPI.SYNCBUSY.bit.ENABLE == 1);
/*CTRLA --> MODE --> 0x3  / switch on SPI MASTER for SERCOM*/
SERCOM0->SPI.CTRLA.bit.MODE = 0x3;
/*CTRLB --> RXENABLE --> 0 / switch off RX, not use MISO*/
SERCOM0->SPI.CTRLB.bit.RXEN = 0;
/*wait for synchro*/
while(SERCOM0->SPI.SYNCBUSY.bit.CTRLB);
/*CTRLA --> DOPO -->  0x1 / in mode MASTER allocate PAD[2] to the MOSI and PAD[3] to the CLK*/
SERCOM0->SPI.CTRLA.bit.DOPO = 0x1;
/*BAUD --> BAUD --> 0 / set Baud Generator (0-255)*/
SERCOM0->SPI.BAUD.reg = 0x0; //for Baud = 0 --> f max = F Core / 2
/*Interrupt flag TXC on and RXC on and DRE on*/
SERCOM0->SPI.INTENSET.bit.TXC = 1;
SERCOM0->SPI.INTENSET.bit.DRE = 1;
/*CTRLA --> ENABLE --> 1 / switch on SPI*/
SERCOM0->SPI.CTRLA.bit.ENABLE = 1;
/*wait for synchro*/
while(SERCOM0->SPI.SYNCBUSY.bit.ENABLE == 1);
/*End  SPI configuration*/
}

void SPI_Sercom0_send(uint8_t data)
{  
    //wait for data register to be empty
    while(!SERCOM0->SPI.INTFLAG.bit.DRE);
    //send data
    SERCOM0->SPI.DATA.reg = data;
     /*wait for transfer complete*/
    while(!SERCOM0->SPI.INTFLAG.bit.TXC);
       
}