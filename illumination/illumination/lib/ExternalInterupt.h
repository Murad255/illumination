/*
 * ExternalInterupt.h
 *
 * Created: 20.07.2018 13:57:09
 *  Author: MY_PC
 debug status: +
	внешнее прерывание пина B1 (INT0)
 */ 
#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
typedef unsigned char byte;
#if !defined(ATMEGA) && !defined(ATTINY)
	#error "Don't defined controller family! Will deifine family (ATMEGA or ATTINY) before add this library."
#endif

volatile byte flag =0;

byte readExInt();
bool availableExInt();
void ExIntBegin();
ISR(INT0_vect)
{
	flag++;
	//PORTB^=1<<5;
}

//####################################################################
		void ExIntBegin(){
			#ifdef ATMEGA
			DDRD&=~(1<<2);
			PORTD |=(1<<2);
			EICRA =(1<<ISC01) | (1<<ISC00);
			EIMSK = (1<<INT0);
			#endif
			
			#ifdef ATTINY
			DDRB &=~(1<<2);
			PORTB |=(1<<2);
			MCUCR=(1<<ISC01) | (1<<ISC00);
			GIMSK= (1<<INT0);
			#endif
			sei();
		}
	byte readExInt(){
		byte n=flag;
		flag =0;
		return n;
	}
	bool availableExInt(){
		if(flag)return 1;
		else return 0;
	}