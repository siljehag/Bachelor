#include <atmel_start.h>
#include <avr/sleep.h>
#include <util/delay.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	set_sleep_mode(SLEEP_MODE_STANDBY);
	

	/* Replace with your application code */
	while (1) {
		_delay_ms(2000);
		sleep_enable();
		sleep_mode();
		//sleep_disable();
		//_delay_ms(2000);
	}
}
