/**
 * \file
 *
 * \brief SPI basic driver.
 *
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *
 */

#include <spi_basic.h>
#include <atmel_start_pins.h>

typedef struct SPI_0_descriptor_s {
	spi_transfer_status_t status;
} SPI_0_descriptor_t;

static SPI_0_descriptor_t SPI_0_desc;

void SPI_0_init()
{

	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600); /* set baud rate register */

	USART0.CTRLA = 0 << USART_ABEIE_bp    /* Auto-baud Error Interrupt Enable: disabled */
	               | 0 << USART_DREIE_bp  /* Data Register Empty Interrupt Enable: disabled */
	               | 0 << USART_LBME_bp   /* Loop-back Mode Enable: disabled */
	               | USART_RS485_OFF_gc   /* RS485 Mode disabled */
	               | 1 << USART_RXCIE_bp  /* Receive Complete Interrupt Enable: enabled */
	               | 0 << USART_RXSIE_bp  /* Receiver Start Frame Interrupt Enable: disabled */
	               | 0 << USART_TXCIE_bp; /* Transmit Complete Interrupt Enable: disabled */

	USART0.CTRLB = 0 << USART_MPCM_bp       /* Multi-processor Communication Mode: disabled */
	               | 0 << USART_ODME_bp     /* Open Drain Mode Enable: disabled */
	               | 1 << USART_RXEN_bp     /* Reciever enable: enabled */
	               | USART_RXMODE_NORMAL_gc /* Normal mode */
	               | 0 << USART_SFDEN_bp    /* Start Frame Detection Enable: disabled */
	               | 1 << USART_TXEN_bp;    /* Transmitter Enable: enabled */

	USART0.CTRLC = USART_CMODE_MSPI_gc       /* Master SPI Mode */
	               | USART_PMODE_DISABLED_gc /* No Parity */
	               | 0 << USART_UCPHA_bp     /* SPI Master Mode, Clock Phase: disabled */
	               | 0 << USART_UDORD_bp     /* SPI Master Mode, Data Order: disabled */
	               | USART_SBMODE_1BIT_gc;   /* 1 stop bit */

	// USART0.DBGCTRL = 0 << USART_ABMBP_bp /* Autobaud majority voter bypass: disabled */
	//		 | 0 << USART_DBGRUN_bp; /* Debug Run: disabled */

	// USART0.EVCTRL = 0 << USART_IREI_bp; /* IrDA Event Input Enable: disabled */

	// USART0.RXPLCTRL = 0x0 << USART_RXPL_gp; /* Receiver Pulse Length: 0x0 */

	// USART0.TXPLCTRL = 0x0 << USART_TXPL_gp; /* Transmit pulse length: 0x0 */

	SPI_0_desc.status = SPI_FREE;
}

void SPI_0_enable()
{
	USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void SPI_0_disable()
{
	USART0.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t SPI_0_exchange_byte(uint8_t data)
{
	// Blocking wait for SPI free makes the function work
	// seamlessly also with IRQ drivers.
	while (SPI_0_desc.status == SPI_BUSY)
		;
	USART0.TXDATAL = data;
	while (!(USART0.STATUS & USART_RXCIF_bm))
		;
	return USART0.RXDATAL;
}