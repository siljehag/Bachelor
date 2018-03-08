
void init_sleepmode(void){
	
	SLPCTRL_CTRLA |= SLPCTRL_SMODE_STDBY_gc | SLPCTRL_SEN_bp;		// Select standby sleepmode, enable selected sleepmode
	
}