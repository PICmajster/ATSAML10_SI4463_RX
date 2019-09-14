/***************************************************************************
  FileName:        delay.h
  Processor:       ATSAML
  IDE :            SEGGER ver 4.16
  Created by:      http://strefapic.blogspot.com
 ***************************************************************************/
/*-------------------------------------------------------------------------*/
/* Delay  configuration                                                    */
/*-------------------------------------------------------------------------*/

#define F_CPU 4000000UL

void portable_delay_cycles(uint32_t n);

#define cpu_ms_2_cy(ms, f_cpu)  (((uint64_t)(ms) * (f_cpu) + (uint64_t)(7e3-1ul)) / (uint64_t)7e3)
#define cpu_us_2_cy(us, f_cpu)  (((uint64_t)(us) * (f_cpu) + (uint64_t)(7e6-1ul)) / (uint64_t)7e6)
#define delay_cycles            portable_delay_cycles
#define cpu_delay_s(delay)      delay_cycles(cpu_ms_2_cy(1000 * delay, F_CPU))
#define cpu_delay_ms(delay)     delay_cycles(cpu_ms_2_cy(delay, F_CPU))
#define cpu_delay_us(delay)     delay_cycles(cpu_us_2_cy(delay, F_CPU))
#define _delay_us    cpu_delay_us
#define _delay_ms    cpu_delay_ms
#define _delay_s     cpu_delay_s




