/***************************************************************************
  FileName:        system.c
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* system configuration                                                    */
/*-------------------------------------------------------------------------*/

#include <saml10e16a.h>
#include "system.h"
#include "clock.h"
#include "pin_manager.h"
#include "spi.h"
#include "eic_manager.h"

void MySystemInit(void)
{
    PIN_Manager_init();
    Clock_Sercom_init();//the sequence is important, first Clock_Sercom() next SPI_Sercom_init()
    SPI_Sercom1_init();
    SPI_Sercom0_init();
    Clock_EIC_init(); //the sequence is important, first Clock_EIC() next EIC_Manager_init()
    EIC_Manager_init();
    
}