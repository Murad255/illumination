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
#define PORT PORTB
#define PWM_PIN 0


							
void ledOff();				
void ledOn(byte bright=0);	
void ledInvert();			
void PWMbegin();			
void Up();					


//##############################################################
void Up(){
	if(OCR0A==0xFF)ledOff();
	else ledOn(OCR0A/51+1);
	return;
}

void PWMbegin(){
	DDR |=1<<PWM_PIN;
	MCUCR|=1<<PUD;
	TCCR0A=0b10100011; //выбираем неинверсный режим шим для обоих светодиодов
	TCCR0B=0b00000001;  //выбираем работу таймера без предделителя тактовой частоты
	}
	
void ledOff(){
	OCR0A=0;
	return;
}

void ledOn(byte bright){
	 static byte n;
		if (bright)OCR0A= n =(bright*51);
		else  OCR0A=n;
	return;
}

void ledInvert(){
	if(OCR0A)ledOff();
	else ledOn();
	return;
}
#endif /* PWM_H_ */