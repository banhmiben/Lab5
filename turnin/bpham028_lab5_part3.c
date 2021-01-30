/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, First, nextUpdate, Next, resetUpdate, Reset} State;
unsigned order[] = {0x00 ,0x01,0x03,0x07,0x0F, 0x1F, 0x3F, 0x7F};
unsigned char i = 0x00;
void Tick_Lights() {

	switch(State) { //transitions
		case Start:
			State = Init;
			break;
		case Init:
			State = First;
			break;
		case First:
			if (i > 0x07) {
				State = resetUpdate;
			} else if ((~PINA & 0x01) == 0x01) {
				State = nextUpdate;
			} else {
				State = First;
			} break;
		case resetUpdate:
			State = Reset;
			break;
		case Reset:
			if ((~PINA & 0x01) != 0x01) {
				State = First;
			} else {
				State = Reset;
			} break;
		case nextUpdate:
			State = Next;
			break;
		case Next:
			if ((~PINA & 0x01) == 0x01) {
				State = Next;
			} else if ((~PINA & 0x01) != 0x01) {
				State = First;
			} break;
		default:
			State = Start;
			break;
	}
	switch(State) {
		case Start:
			PORTB = 0x00;
			break;
		case Init:
			PORTB = 0x00;
			break;
		case First:
			break;
		case resetUpdate:
			//PORTB = 0x00;
			//i = 0;
			break;
		case Reset:
			PORTB = 0x00;
			i = 0;
			break;
		case nextUpdate:
			PORTB = order[++i];
			break;
		case Next:
			break;
		default:
			PORTB = 0x00;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
		Tick_Lights();
    }
    return 1;
}
