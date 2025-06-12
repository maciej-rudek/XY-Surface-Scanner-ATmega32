#ifndef __PLATFORM_NATIVE__
	#include <Arduino.h>
#endif
// #include<avr/io.h>
// #include<avr/interrupt.h>
#include "../include/initial.h"

#define F_CPU 11059200
#define BAUD 115200
#define MYUBRR F_CPU/16/BAUD-1

#ifndef __PLATFORM_NATIVE__
	void SPI_MasterInit();
	void IoInit();
	void UartInit();

	// struct sUART sU;


	void UartInit()
	{
		unsigned int baud = MYUBRR;
		#ifndef __PLATFORM_NATIVE__
			UBRRH = (unsigned char)(baud>>8);
			UBRRL = (unsigned char)baud;
			UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
			UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
		#endif
	}

	void SPI_MasterInit()
	{
		#ifndef __PLATFORM_NATIVE__
			DDRB=0xBF;
			//SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0)|(0<<DORD);
			SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0)|(0<<CPOL)|(1<<CPHA);
			SPSR = (1<<SPI2X);
		#endif
	}

	void IoInit()
	{
		#ifndef __PLATFORM_NATIVE__
			DDRA	= 0xFF;
			PORTA	= 0b00000010;

			DDRB	= 0xFB;
			PORTB	= 0x00;

			DDRC	= 0b11100011;
			PORTC	= 0b11101111;
			
			DDRD	= 0xFF;
			PORTD	= 0xFE;		// RxD - wejscie
		#endif
	}
#endif