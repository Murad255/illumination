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
typedef unsigned char byte;
#define DDR DDRB
#define PORT PORTB
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
		DDR &=~(1<<2);
		PORT |=(1<<2);
		//EICRA 
		MCUCR=(1<<ISC01) | (1<<ISC00);
		//EIMSK 
		GIMSK= (1<<INT0);
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