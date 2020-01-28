/*
 * PWM.h
 *
 * Created: 20.07.2018 13:57:09
 *  Author: MY_PC
 debug status: +
 */ 
  #pragma once
#include <avr/io.h>
#include "watcdog.h"

typedef unsigned char byte;

#ifndef PWM_H_
#define PWM_H_

#define DDR		DDRB
#define PORT	PORTB
#define PWM_PIN 0


class Led
{
	byte brightness;
	void setImputValue(unsigned char value);
	byte getImputValue();
	
	public:
	void ledOff();
	void ledOn(byte bright=0);	//задаёт яркость в 5 уровнях
	void ledInvert();
	void ledInvert(int changeTime);
	Led();						//инизиализация светодиода, сделует указать в начале
	void Up();					//повысить яркость на уровень. если установлен 5 уровень, то установить 1
};					




//##############################################################
void Led::Up(){
	if(getImputValue()==0xFF)ledOn(1);
	else ledOn(getImputValue()/51+1);
	return;
}

 Led::Led(){
	DDRB |=1<<0;
	MCUCR|=1<<PUD;
	TCCR0A=0b10000001; //выбираем неинверсный режим шим для обоих светодиодов
	TCCR0B=0b00000001;  //выбираем работу таймера без предделителя тактовой частоты
	}
	
void Led::ledOff(){
	setImputValue(0);
	return;
}

void Led::ledOn(byte bright){
		if (bright)setImputValue(brightness =(bright*51));
		else  setImputValue(brightness);
	return;
}

void Led::ledInvert(){
	if(getImputValue())ledOff();
	else ledOn();
	return;
}

void Led::ledInvert(int changeTime){
	int n=changeTime/16;
	n=brightness/n;
	
	if(getImputValue()) 
	for(int i=changeTime/16; i>=0; i--){
		setImputValue(i*n);
		delay(16);
	}
	
	else
	for(int i=0; i<=changeTime/16; i++){
		setImputValue(i*n);
		delay(16);
	}
	
	return;
}

/////////////////////////////////////////////

void Led::setImputValue(byte value){
	 OCR0A=value;//255-value;
}

byte Led::getImputValue(){
	return OCR0A;//255-OCR0A;
}
#endif /* PWM_H_ */