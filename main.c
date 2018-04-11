#include <avr/io.h>
#include <util/delay.h>
#include "myUSART.h"


const struct State
{
	unsigned char Out; // output to Port B //
	//unsigned int Time; // seconds to wait //
	const struct State *Next[4]; // next state from inputs: 00,01,10,11 //
};


#define NorthGreen 			&fsm[0]
#define NorthYellow 		&fsm[1]
#define EastGreen			&fsm[2]
#define EastYellow			&fsm[3]
#define NorthY_Walk 		&fsm[4]
#define EastY_Walk			&fsm[5]
#define FlashY_ON_North 	&fsm[6]
#define FlashY_OFF_North	&fsm[7]
#define FlashY_ON_East		&fsm[8]
#define FlashY_OFF_East		&fsm[9]

StateType fsm[10] = {
	{0b00100001,{NorthGreen,NorthGreen,NorthY_Walk,NorthYellow}}, // NorthGreen //
	{0b00010001,{NorthYellow,EastGreen,FlashY_ON_North,EastGreen}} // NorthYellow //
	{0b00001100,{EastGreen,EastGreen,EastY_Walk,EastYellow}}, // EastGreen //
	{0b00001010,{EastYellow,NorthGreen,FlashY_ON_East,NorthGreen}}, // EastYellow //
	{0b00100001,{NorthY_Walk,FlashY_ON_North,NorthY_Walk,FlashY_ON_North}}, // NorthY_Walk //
	{0b00001010,{EastY_Walk,FlashY_ON_East,EastY_Walk,FlashY_ON_East}}, // EastY_Walk //
	{0b00010010,{FlashY_ON_North,FlashY_OFF_North,FlashY_ON_North,FlashY_OFF_North}}, // FlashY_ON_North //
	{0b00000000,{FlashY_OFF_North,FlashY_ON_North,FlashY_OFF_North,EastGreen}}, // FlashY_OFF_North //
	{0b00010010,{FlashY_ON_East,FlashY_OFF_East,FlashY_ON_East,FlashY_OFF_East}}, // FlashY_ON_East //
	{0b00000000,{FlashY_OFF_East,FlashY_ON_East,FlashY_OFF_East,NorthGreen}} // FlashY_OFF_East //
}

StateType *Pt; // current state //

int main()
{
	unsigned char Input;
	DDRB = 0xFF;
	DDRD = 0x00;

	while(1)
	{
		// 00 = Flag Timer did not reach
		// 01 = Flag Timer reached short
		// 10 = Flag Ext. Interrupt from Button; note: once activated use cli() or sei()
		// 11 = Flag Timer reached long
		PORTB = Pt -> Out;	// perform output //
		//Wait1sec(Pt -> Time); // time to wait //
		//Input = PORTC&0x03; 
		Pt = Pt -> Next[Input];
	}
return 0;
}
