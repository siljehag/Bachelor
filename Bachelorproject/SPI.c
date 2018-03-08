
 // SPI.c
 

void SPI_init(void){
	
	SPI0_CTRLA |= SPI_MASTER_bm | SPI_PRESC1_bp | SPI_ENABLE_bm;		// Enable master mode, prescale bit 1, enable SPI
	SPI0_CTRLB |= SPI_BUFEN_bp | SPI_SSD_bp | SPI_MODE_2_gc;			// Enable buffer mode, disable slave select, spi mode 2
	SPI0_INTCTRL |= SPI_RXCIE_bp;										// Enable receive complete interrupt
	sei();
}
