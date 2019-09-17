/***************************************************************************
  FileName:        main.c
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* SI4463 RF Transciver RX receive test                                      */
/*-------------------------------------------------------------------------*/
//    Signal SI4463 ---> MCU ATSAML10E16
//     MOSI                     --> PA10  
//     MISO                     --> PA09  
//     SCK                      --> PA11  
//     nSEL                     --> PA08  
//     SDN                      --> PA02  
//     IRQ                      --> PA03  
//     GPIO0                    --> PA16  
//                              
//----------------------------------------
//     LED                      --> PA27
//
/*-------------------------------------------------------------------------*/
/* ILI9341 LCD TFT 320x240 SPI connect                                        */
/*-------------------------------------------------------------------------*/
//    Signal LCD ---> MCU ATSAML10E16
//     CS     (Chip Select)     --> Ground
//     RESET                    --> PA06
//     DC/RS  (Command / Data)  --> PA07
//     MOSI   (Serial Data)     --> PA24
//     SCK    (Serial Clock)    --> PA25
//     LED                      --> +3.3V
//***************************************************************************

#include <saml10e16a.h>
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "system.h"
#include "spi.h"
#include "eic_manager.h"
#include "radio_config_Si4463.h"
#include "si4463.h"
#include "ili9341.h"


void SysTick_Stop(void);
void SysTick_Start(void);

#define LED_TOG (REG_PORT_OUTTGL0 = PORT_PA27)  //toggle PA27

uint8_t receive_buff[64];
uint16_t volatile licznik = 0 ; //for RX, number of received message
volatile uint8_t irq_flag = 0;

int main(void)
{
  /*Select BUCK converter as the main voltage regulator in active mode*/
  //SUPC->VREG.bit.SEL = 1; 
  /* Wait for the regulator switch to be completed */
  //while(!(SUPC->STATUS.reg & SUPC_STATUS_VREGRDY));
  
  /* Initialize the SAM system */
    SystemInit();   //standard system init
    MySystemInit(); //user system init
 
    ili9341_init();
    setOrientation(PORTRAIT); //PORTRAIT, LANSCAPE, PORTRAIT_REV, LANDSCAPE_REV  

    putString("Test SI4463 RX", 30, 30, 2, GREEN_YELLOW);
    
    SI4463_Init();
    SI4463_RX_Start( 0, 0 ); //start received
    SI4463_Get_Interrupt(inter_buff); //get interrupt status and clear interrupt
           
    EIC3_Start(); //start interrupt from EIC
    
    while (1)
    {
      
      /*wait for the irq_flag flag and display the counter of sent messages on the LCD display*/
       if(irq_flag) {
              irq_flag = 0;
              //clr(30, 100, 5);
              putInteger(licznik,30, 100,3,YELLOW); // display counter
              //clr(30, 150, 8);
              putString(receive_buff, 30, 150, 3, YELLOW); // display received data       
           }
          
      }
  }


/* Routime Interrupt */
void EIC_3_Handler(void){
        SI4463_Get_Interrupt(inter_buff); //get interrupt status and clear interrupt
        if(inter_buff[2] & 0x10) {//PACKET RX PEND interruption ? , see API Documentation GET_INT_STATUS
          if(!(inter_buff[2] & 0x08)) {//CRC_ERROR_PEND interruption ?? CRC data interruption Error ? see API Documentation GET_INT_STATUS)
            SI4463_RX_FIFO ( receive_buff, SI4463_Get_Packet_Info()  ); //rewrite data from the RX FIFO (hardware buffer) to the receive_buff (user buffer) 
            licznik++;  
            irq_flag = 1;
            LED_TOG;
           }
         }
       SI4463_Clear_RX_FIFO();
       SI4463_RX_Start( 0, 0 );  
       SI4463_Get_Interrupt(inter_buff); //get interrupt status and clear 
       /* Clear EIC Flag */
       EIC->INTFLAG.reg |= EIC_INTFLAG_EXTINT(1<<3);    
}



