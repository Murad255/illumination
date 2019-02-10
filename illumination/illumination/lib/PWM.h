/*
 * PWM.h
 *
 * Created: 20.07.2018 13:57:09
 *  Author: MY_PC
 debug status: +
 */ 
  #pragma once
#include <avr/io.h>
typedef unsigned char byte;

#ifndef PWM_H_
#define PWM_H_
#define DDR DDRB
#define PWM_PIN 0
bool f=0;
static byte i;   //последнее значение €ркости

							
void ledOff();				
void ledOn(byte bright=i);	
void ledInvert();			
void PWMbegin();			
void Up();					


//##############################################################
void Up(){
	if(i>4){
	ledOff();
	i=0;
	}
	else ledOn(++i);
	return;
}
	void PWMbegin(){
		DDR =1<<PWM_PIN;
		TCCR0A=0b10100011; //выбираем неинверсный режим шим дл€ обоих светодиодов
		TCCR0B=0b00000001;  //выбираем работу таймера без предделител€ тактовой частоты
	}
void ledOff(){
	OCR0A=0;
	f=0;
	return;
}

void ledOn(byte bright){
	f=1;
	i=bright;
	OCR0A=(bright*51);
	return;
}

void ledInvert(){
	
	if(f==0)ledOn();
	else if(f==1)ledOff();
	return;
}
#endif /* PWM_H_ */