#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"

char readButtons();
void writeLED (char);

int main()
{
	char msg;

	DDRB = 0xFF; //Using Pin 8 - 11 for the LEDS as outputs
	DDRC = 0xF0; //Using Pin A0-A3 for buttons as inputs

	initUSART(USART_BAUDRATE);

	while(1)
	{
		//transmit
		msg = readButtons();
		USARTtransmit(msg);

		//receive
		msg = USARTreceive();
		writeLED(msg);
	}
return 0;
}


//////// accept input from buttons ////////
char readButtons()
{
	 char num;  
	 num = PINC; //read port C input value
	 num = ~num; //since port C active low, complement every bit
	 num &= 0x0F; //mask byte and clear high nibble
	 return num;
}

/////// display message to LEDs /////////
void writeLED( char num)
{
	PORTB = num; //display number
	_delay_ms(20);
	PORTB = 0x00;
}