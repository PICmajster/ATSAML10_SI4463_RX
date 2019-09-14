/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2019 SEGGER Microcontroller GmbH             *
*                                                                    *
*           www.segger.com     Support: support@segger.com           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* - Neither the name of SEGGER Microcontroller GmbH                  *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED.                                                        *
* IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
*********************************************************************/

/*****************************************************************************
 *                         Preprocessor Definitions                          *
 *                         ------------------------                          *
 * VECTORS_IN_RAM                                                            *
 *                                                                           *
 *   If defined, an area of RAM will large enough to store the vector table  *
 *   will be reserved.                                                       *
 *                                                                           *
 *****************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 2

/*****************************************************************************
 * Default Exception Handlers                                                *
 *****************************************************************************/

  .thumb_func
  .weak NMI_Handler
NMI_Handler:
  b .

  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
  b .

  .thumb_func
  .weak SVC_Handler
SVC_Handler:
  b .

  .thumb_func
  .weak PendSV_Handler
PendSV_Handler:
  b .

  .thumb_func
  .weak SysTick_Handler
SysTick_Handler:
  b .

  .thumb_func
Dummy_Handler:
  b .

#if defined(__OPTIMIZATION_SMALL)

  .weak SYSTEM_Handler
  .thumb_set SYSTEM_Handler,Dummy_Handler

  .weak WDT_Handler
  .thumb_set WDT_Handler,Dummy_Handler

  .weak RTC_Handler
  .thumb_set RTC_Handler,Dummy_Handler

  .weak EIC_0_Handler
  .thumb_set EIC_0_Handler,Dummy_Handler

  .weak EIC_1_Handler
  .thumb_set EIC_1_Handler,Dummy_Handler

  .weak EIC_2_Handler
  .thumb_set EIC_2_Handler,Dummy_Handler

  .weak EIC_3_Handler
  .thumb_set EIC_3_Handler,Dummy_Handler

  .weak EIC_OTHER_Handler
  .thumb_set EIC_OTHER_Handler,Dummy_Handler

  .weak FREQM_Handler
  .thumb_set FREQM_Handler,Dummy_Handler

  .weak NVMCTRL_Handler
  .thumb_set NVMCTRL_Handler,Dummy_Handler

  .weak PORT_Handler
  .thumb_set PORT_Handler,Dummy_Handler

  .weak DMAC_0_Handler
  .thumb_set DMAC_0_Handler,Dummy_Handler

  .weak DMAC_1_Handler
  .thumb_set DMAC_1_Handler,Dummy_Handler

  .weak DMAC_2_Handler
  .thumb_set DMAC_2_Handler,Dummy_Handler

  .weak DMAC_3_Handler
  .thumb_set DMAC_3_Handler,Dummy_Handler

  .weak DMAC_OTHER_Handler
  .thumb_set DMAC_OTHER_Handler,Dummy_Handler

  .weak EVSYS_0_Handler
  .thumb_set EVSYS_0_Handler,Dummy_Handler

  .weak EVSYS_1_Handler
  .thumb_set EVSYS_1_Handler,Dummy_Handler

  .weak EVSYS_2_Handler
  .thumb_set EVSYS_2_Handler,Dummy_Handler

  .weak EVSYS_3_Handler
  .thumb_set EVSYS_3_Handler,Dummy_Handler

  .weak EVSYS_NSCHK_Handler
  .thumb_set EVSYS_NSCHK_Handler,Dummy_Handler

  .weak PAC_Handler
  .thumb_set PAC_Handler,Dummy_Handler

  .weak SERCOM0_0_Handler
  .thumb_set SERCOM0_0_Handler,Dummy_Handler

  .weak SERCOM0_1_Handler
  .thumb_set SERCOM0_1_Handler,Dummy_Handler

  .weak SERCOM0_2_Handler
  .thumb_set SERCOM0_2_Handler,Dummy_Handler

  .weak SERCOM0_OTHER_Handler
  .thumb_set SERCOM0_OTHER_Handler,Dummy_Handler

  .weak SERCOM1_0_Handler
  .thumb_set SERCOM1_0_Handler,Dummy_Handler

  .weak SERCOM1_1_Handler
  .thumb_set SERCOM1_1_Handler,Dummy_Handler

  .weak SERCOM1_2_Handler
  .thumb_set SERCOM1_2_Handler,Dummy_Handler

  .weak SERCOM1_OTHER_Handler
  .thumb_set SERCOM1_OTHER_Handler,Dummy_Handler

  .weak SERCOM2_0_Handler
  .thumb_set SERCOM2_0_Handler,Dummy_Handler

  .weak SERCOM2_1_Handler
  .thumb_set SERCOM2_1_Handler,Dummy_Handler

  .weak SERCOM2_2_Handler
  .thumb_set SERCOM2_2_Handler,Dummy_Handler

  .weak SERCOM2_OTHER_Handler
  .thumb_set SERCOM2_OTHER_Handler,Dummy_Handler

  .weak TC0_Handler
  .thumb_set TC0_Handler,Dummy_Handler

  .weak TC1_Handler
  .thumb_set TC1_Handler,Dummy_Handler

  .weak TC2_Handler
  .thumb_set TC2_Handler,Dummy_Handler

  .weak ADC_OTHER_Handler
  .thumb_set ADC_OTHER_Handler,Dummy_Handler

  .weak ADC_RESRDY_Handler
  .thumb_set ADC_RESRDY_Handler,Dummy_Handler

  .weak AC_Handler
  .thumb_set AC_Handler,Dummy_Handler

  .weak DAC_UNDERRUN_A_Handler
  .thumb_set DAC_UNDERRUN_A_Handler,Dummy_Handler

  .weak DAC_EMPTY_Handler
  .thumb_set DAC_EMPTY_Handler,Dummy_Handler

  .weak PTC_Handler
  .thumb_set PTC_Handler,Dummy_Handler

  .weak TRNG_Handler
  .thumb_set TRNG_Handler,Dummy_Handler

  .weak TRAM_Handler
  .thumb_set TRAM_Handler,Dummy_Handler

#else

  .thumb_func
  .weak SYSTEM_Handler
SYSTEM_Handler:
  b .

  .thumb_func
  .weak WDT_Handler
WDT_Handler:
  b .

  .thumb_func
  .weak RTC_Handler
RTC_Handler:
  b .

  .thumb_func
  .weak EIC_0_Handler
EIC_0_Handler:
  b .

  .thumb_func
  .weak EIC_1_Handler
EIC_1_Handler:
  b .

  .thumb_func
  .weak EIC_2_Handler
EIC_2_Handler:
  b .

  .thumb_func
  .weak EIC_3_Handler
EIC_3_Handler:
  b .

  .thumb_func
  .weak EIC_OTHER_Handler
EIC_OTHER_Handler:
  b .

  .thumb_func
  .weak FREQM_Handler
FREQM_Handler:
  b .

  .thumb_func
  .weak NVMCTRL_Handler
NVMCTRL_Handler:
  b .

  .thumb_func
  .weak PORT_Handler
PORT_Handler:
  b .

  .thumb_func
  .weak DMAC_0_Handler
DMAC_0_Handler:
  b .

  .thumb_func
  .weak DMAC_1_Handler
DMAC_1_Handler:
  b .

  .thumb_func
  .weak DMAC_2_Handler
DMAC_2_Handler:
  b .

  .thumb_func
  .weak DMAC_3_Handler
DMAC_3_Handler:
  b .

  .thumb_func
  .weak DMAC_OTHER_Handler
DMAC_OTHER_Handler:
  b .

  .thumb_func
  .weak EVSYS_0_Handler
EVSYS_0_Handler:
  b .

  .thumb_func
  .weak EVSYS_1_Handler
EVSYS_1_Handler:
  b .

  .thumb_func
  .weak EVSYS_2_Handler
EVSYS_2_Handler:
  b .

  .thumb_func
  .weak EVSYS_3_Handler
EVSYS_3_Handler:
  b .

  .thumb_func
  .weak EVSYS_NSCHK_Handler
EVSYS_NSCHK_Handler:
  b .

  .thumb_func
  .weak PAC_Handler
PAC_Handler:
  b .

  .thumb_func
  .weak SERCOM0_0_Handler
SERCOM0_0_Handler:
  b .

  .thumb_func
  .weak SERCOM0_1_Handler
SERCOM0_1_Handler:
  b .

  .thumb_func
  .weak SERCOM0_2_Handler
SERCOM0_2_Handler:
  b .

  .thumb_func
  .weak SERCOM0_OTHER_Handler
SERCOM0_OTHER_Handler:
  b .

  .thumb_func
  .weak SERCOM1_0_Handler
SERCOM1_0_Handler:
  b .

  .thumb_func
  .weak SERCOM1_1_Handler
SERCOM1_1_Handler:
  b .

  .thumb_func
  .weak SERCOM1_2_Handler
SERCOM1_2_Handler:
  b .

  .thumb_func
  .weak SERCOM1_OTHER_Handler
SERCOM1_OTHER_Handler:
  b .

  .thumb_func
  .weak SERCOM2_0_Handler
SERCOM2_0_Handler:
  b .

  .thumb_func
  .weak SERCOM2_1_Handler
SERCOM2_1_Handler:
  b .

  .thumb_func
  .weak SERCOM2_2_Handler
SERCOM2_2_Handler:
  b .

  .thumb_func
  .weak SERCOM2_OTHER_Handler
SERCOM2_OTHER_Handler:
  b .

  .thumb_func
  .weak TC0_Handler
TC0_Handler:
  b .

  .thumb_func
  .weak TC1_Handler
TC1_Handler:
  b .

  .thumb_func
  .weak TC2_Handler
TC2_Handler:
  b .

  .thumb_func
  .weak ADC_OTHER_Handler
ADC_OTHER_Handler:
  b .

  .thumb_func
  .weak ADC_RESRDY_Handler
ADC_RESRDY_Handler:
  b .

  .thumb_func
  .weak AC_Handler
AC_Handler:
  b .

  .thumb_func
  .weak DAC_UNDERRUN_A_Handler
DAC_UNDERRUN_A_Handler:
  b .

  .thumb_func
  .weak DAC_EMPTY_Handler
DAC_EMPTY_Handler:
  b .

  .thumb_func
  .weak PTC_Handler
PTC_Handler:
  b .

  .thumb_func
  .weak TRNG_Handler
TRNG_Handler:
  b .

  .thumb_func
  .weak TRAM_Handler
TRAM_Handler:
  b .

#endif

/*****************************************************************************
 * Vector Table                                                              *
 *****************************************************************************/

  .section .vectors, "ax"
  .align 2
  .global _vectors
  .extern __stack_end__
  .extern Reset_Handler

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word SYSTEM_Handler
  .word WDT_Handler
  .word RTC_Handler
  .word EIC_0_Handler
  .word EIC_1_Handler
  .word EIC_2_Handler
  .word EIC_3_Handler
  .word EIC_OTHER_Handler
  .word FREQM_Handler
  .word NVMCTRL_Handler
  .word PORT_Handler
  .word DMAC_0_Handler
  .word DMAC_1_Handler
  .word DMAC_2_Handler
  .word DMAC_3_Handler
  .word DMAC_OTHER_Handler
  .word EVSYS_0_Handler
  .word EVSYS_1_Handler
  .word EVSYS_2_Handler
  .word EVSYS_3_Handler
  .word EVSYS_NSCHK_Handler
  .word PAC_Handler
  .word SERCOM0_0_Handler
  .word SERCOM0_1_Handler
  .word SERCOM0_2_Handler
  .word SERCOM0_OTHER_Handler
  .word SERCOM1_0_Handler
  .word SERCOM1_1_Handler
  .word SERCOM1_2_Handler
  .word SERCOM1_OTHER_Handler
  .word SERCOM2_0_Handler
  .word SERCOM2_1_Handler
  .word SERCOM2_2_Handler
  .word SERCOM2_OTHER_Handler
  .word TC0_Handler
  .word TC1_Handler
  .word TC2_Handler
  .word ADC_OTHER_Handler
  .word ADC_RESRDY_Handler
  .word AC_Handler
  .word DAC_UNDERRUN_A_Handler
  .word DAC_EMPTY_Handler
  .word PTC_Handler
  .word TRNG_Handler
  .word TRAM_Handler
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 2
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
