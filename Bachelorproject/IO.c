/*
 * IO.c
 *
 * Created: 22.02.2018 13.49.00
 *  Author: uioit
 */ 

void init_io(void){
	
	PORTx.DIR |= 0b						//Sets Px .. as output
	PORTx.PINyCTRL |= (1<<...)			//Turns on pull-up resistor on PORTxy
	
}
