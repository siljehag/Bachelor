/*
 * RTC.c
 *
 * Created: 22.02.2018 13.47.35
 *  Author: uioit
 */ 

#define COUNTER 64000
#define F_CPU 32000							// 32kHz clock with prescaler 1 --> 32kHz

void init_rtc(void){
	
	RTC_CLKSEL = RTC_CLKSEL_INT32K_gc		// Clock source 32kHz internal oscillator
	
	RTC_PER = COUNTER;						// Timer period 64000*1/32000 = 2s (counter*prescaler/clock)
	
	RTC_INTCTRL |= (1<< RTC_OVF_bm);		// Interrupt on counter overflow enabled
	
	RTC_CTRLA = RTC_RTCEN_bm | RTC_RUNSTDBY_bm | RTC_PRESCALER_DIV1_gc;			//RTC enabled, RTC enabled in sleepmode, prescale 1
	
}