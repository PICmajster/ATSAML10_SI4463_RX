/***************************************************************************
  FileName:        clock.h
  Processor:       ATSAML10E16A
  IDE :            SEGGER ver 4.12
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* CLOCK configuration- core + Peripheral                                  */
/*-------------------------------------------------------------------------*/
//      
//    core clock : 4 MHz
//    
//    
//
//***************************************************************************

//void ClockCore_set(void);
void Clock_Sercom_init(void);
void Clock_EIC_init(void);