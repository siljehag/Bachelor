/*
 * Bachelorproject.c
 *
 * Created: 21.02.2018 12.13.22tore pang
 * Author : uioit
 */ 

#include <avr/io.h>


int main(void)
{
	clk_init();
	init_rtc();
	init_sleepmode();
	SPI_init();
	init_io();
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

