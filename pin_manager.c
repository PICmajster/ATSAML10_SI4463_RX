/***************************************************************************
  FileName:        pin_manager.c
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* PORT (pin) configuration                                                */
/*-------------------------------------------------------------------------*/
#include <saml10e16a.h>
#include "pin_manager.h"

void PIN_Manager_init(void){
/****************************************************************************
* Setting direction to Output 
****************************************************************************/
PORT->Group[0].DIRSET.reg = PORT_PA02 | PORT_PA08;//Set pin PA02,PA08 direction to Output for SI4463
PORT->Group[0].DIRSET.reg = PORT_PA06 | PORT_PA07;//Set pin PA06,PA07 direction to Output for LCD
PORT->Group[0].DIRSET.reg = PORT_PA27;//Set pin PA27 direction to Output for LED


/****************************************************************************
* Setting direction to Input 
****************************************************************************/

PORT->Group[0].DIRCLR.reg = PORT_PA16;//Set pin PA16 direction to Input for GPIO0 SI4463

/****************************************************************************
* Setting the Pull Up see page 629 in datasheet
****************************************************************************/

PORT->Group[0].PINCFG[16].bit.INEN = 1 ;//Set pin PA16 Input Enable
PORT->Group[0].PINCFG[16].bit.PULLEN = 1 ;//Set pin PA16 PULL Enable
PORT->Group[0].OUTCLR.reg = PORT_PA16 ;//Set pin PA16 PULL DOWN 

/****************************************************************************
* Setting PINMUX  
****************************************************************************/
/*PORTA --> PINCFG9 --> PMUXEN --> 1 / connect PA09 to the module PMUX*/
PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;
/*PORTA --> PINCFG10 --> PMUXEN --> 1 / connect PA10 to the module PMUX*/
PORT->Group[0].PINCFG[10].bit.PMUXEN = 1;
/*PORTA --> PINCFG11 --> PMUXEN --> 1 / connect PA11 to the module PMUX*/
PORT->Group[0].PINCFG[11].bit.PMUXEN = 1;

/*PORTA --> PINCFG24 --> PMUXEN --> 1 / connect PA24 to the module PMUX*/
PORT->Group[0].PINCFG[24].bit.PMUXEN = 1;
/*PORTA --> PINCFG25 --> PMUXEN --> 1 / connect PA25 to the module PMUX*/
PORT->Group[0].PINCFG[25].bit.PMUXEN = 1;

/*PORTA --> PINCFG3 --> PMUXEN --> 1 / connect PA03 to the module PMUX*/
PORT->Group[0].PINCFG[3].bit.PMUXEN = 1;


/****************************************************************************
* Setting connect PINMUX to Peripheral  
****************************************************************************/
/*PORTA --> PMUX4 --> PMUXO --> 0x2 / connect PA09 (odd pin 2*n+1) to the module SERCOM1 (put C)*/
/*Pin  9 = 2*n+1 stąd n = (9-1)/2 = 4 */
PORT->Group[0].PMUX[4].bit.PMUXO = 0x2;
/*PORTA --> PMUX5 --> PMUXE --> 0x2 / connect PA10 (even pin 2*n) to the module SERCOM1 (put C)*/
/*Pin  10 = 2*n stąd n = 10/2 = 5 */
PORT->Group[0].PMUX[5].bit.PMUXE = 0x2;
/*PORTA --> PMUX5 --> PMUXO --> 0x2 / connect PA11 (odd pin 2*n+1) to the module SERCOM1 (put C)*/
/*Pin  11 = 2*n+1 stąd n = (11-1)/2 = 4 */
PORT->Group[0].PMUX[5].bit.PMUXO = 0x2;

/*PORTA --> PMUX12 --> PMUXO --> 0x2 / connect PA24 (even pin 2*n) to the module SERCOM0 (put C)*/
/*Pin  24 = 2*n stąd n = 24/2 = 12 */
PORT->Group[0].PMUX[12].bit.PMUXE = 0x2;
/*PORTA --> PMUX1 --> PMUXE --> 0x2 / connect PA25 (odd pin 2*n+1) to the module SERCOM0 (put C)*/
/*Pin  25 = 2*n+1 stąd n = (25 - 1)/2 = 12 */
PORT->Group[0].PMUX[12].bit.PMUXO = 0x2;

/*PORTA --> PMUX1 --> PMUXO --> 0x0 / connect PA03 (odd pin 2*n+1) to the module EIC (put A)*/
/*Pin  3 = 2*n+1 stąd n = (3-1)/2 = 1 */
PORT->Group[0].PMUX[1].bit.PMUXO = 0x0;

}