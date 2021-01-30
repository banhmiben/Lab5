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

enum States {Start, Init, Wait, WaitInc ,Inc, WaitDec, Dec, Reset} State;

unsigned char tmpA = 0x00;
void Tick() {

	tmpA = ~PINA;

	switch(State) {
		case Start:
			State = Init;
			break;
		case Init:
			State = Wait;
			break;
		case Wait:
			if (tmpA == 0x03) {
				State = Reset;
			} else if (tmpA == 0x01) {
				State = WaitInc;
			} else if (tmpA == 0x02) {
				State = WaitDec;
			} break;
		case WaitInc:	
			State = Inc;
			break;
		case Inc:
			if (tmpA == 0x01) {
				State = Inc;
			} else {
				State = Wait;
			} break;
		case WaitDec:
			State = Dec;
			break;
		case Dec:
			if (tmpA == 0x02) {
				State = Dec;
			} else {
				State = Wait;
			} break;
		case Reset:
			if (tmpA == 0x03) {
				State = Reset;
			} else {
				State = Wait;
			} break;
		default:
			State = Start;
			break;
	}

	switch(State) {
		case Start:
			break;
		case Init:
			PORTC = 0x07;
			break;
		case Wait:
			break;
		case Inc:
			break;
		case Dec:
			break;
		case WaitInc:
			if (PORTC < 9) {
				++PORTC;
			} break;
		case WaitDec:
			if (PORTC > 0) {
				--PORTC;
			} break;
		case Reset:
			PORTC = 0;
			break;
		default:
			PORTC = 0x07;
			break;
	}

}



int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	State = Start;

	while(1) {
		Tick();
	}
	return 1;

}
