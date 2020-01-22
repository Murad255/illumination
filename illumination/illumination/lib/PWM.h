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

#define DDR		DDRB
#define PORT	PORTB
#define PWM_PIN 0


							
void ledOff();				
void ledOn(byte bright=0);	
void ledInvert();			
void PWMbegin();			
void Up();					

namespace privatePWM{
	void setImputValue(unsigned char value);
	byte getImputValue();
}


//##############################################################
void Up(){
	if(privatePWM::getImputValue()==0xFF)ledOn(1);
	else ledOn(privatePWM::getImputValue()/51+1);
	return;
}

void PWMbegin(){
	DDR |=1<<PWM_PIN;
	MCUCR|=1<<PUD;
	TCCR0A=0b10100011; //выбираем неинверсный режим шим для обоих светодиодов
	TCCR0B=0b00000001;  //выбираем работу таймера без предделителя тактовой частоты
	}
	
void ledOff(){
	privatePWM::setImputValue(0);
	return;
}

void ledOn(byte bright){
	 static byte n;
		if (bright)privatePWM::setImputValue(n =(bright*51));
		else  privatePWM::setImputValue(n);
	return;
}

void ledInvert(){
	if(privatePWM::getImputValue())ledOff();
	else ledOn();
	return;
}



void privatePWM::setImputValue(byte value){
	 OCR0A=255-value;
}

byte privatePWM::getImputValue(){
	return 255-OCR0A;
}
#endif /* PWM_H_ */