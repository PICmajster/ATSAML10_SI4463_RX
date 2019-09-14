/***************************************************************************
  FileName:        delay.h
  Processor:       ATSAML
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* Delay function                                                          */
/*-------------------------------------------------------------------------*/
#include <saml10e16a.h>
#include "delay.h"

void portable_delay_cycles(uint32_t n)
{
    __asm (
    "loop: DMB    \n"
    #ifdef __ICCARM__
    "SUBS r0, r0, #1 \n"
    #else
    "SUB r0, r0, #1 \n"
    #endif
    "CMP r0, #0  \n"
    "BNE loop         "
    );
}