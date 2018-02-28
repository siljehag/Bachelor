

 // Clock.c


void clk_init(void){
	
CLKCTRL_MCLKCTRLA |= CLKCTRL_CLKSEL_OSCULP32K_gc;			// Enable 32kHz ULP clock as main clock
CLKCTRL_OSC32KCTRLA |= CLKCTRL_RUNSTDBY_bm;					// Enable run in sleepmode
}