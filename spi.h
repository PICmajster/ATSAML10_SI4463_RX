/***************************************************************************
  FileName:        spi.h
  Processor:       ATSAML10E16
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* SPI configuration                                                       */
/*-------------------------------------------------------------------------*/
//      
//   Reqired SPI connections :
//     Signal SI4463 ---> MCU ATSAML10E16
//     MOSI                     --> PA10
//     MISO                     --> PA09
//     SCK                      --> PA11
//
//***************************************************************************

void SPI_Sercom1_init(void);
void SPI_Sercom0_init(void);
uint8_t SPI_Exchange8bit(uint8_t data);
void SPI_Sercom0_send(uint8_t data);