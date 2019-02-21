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
#include <math.h>
#include "watcdog.h"
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
////Smoother//////

#define value 15

//volatile bool status = 1;
volatile int coint=0,a;							//коэффициент дл€ преобразовани€ {0,2}в {pastCoint,nextCoint}
int  nextCoint;
void S_Change();
void CointNum(int lev);
void CointTime(int lev);

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
	CointTime(0);
	f=0;
	return;
}

void ledOn(byte bright){
	f=1;
	i=bright;
	CointTime(bright*51);
	return;
}

void ledInvert(){
	
	if(f==0)ledOn();
	else if(f==1)ledOff();
	return;
}

void CointNum(int lev) {

	nextCoint = lev;
	a = (lev - coint)/ value;
	if (a == 0)a = 1;
	if (a <0)a = -a;
}
void CointTime(int lev){
	CointNum(lev);
	while(1){
		if (a > (nextCoint - coint))a = 1;
		if (coint == nextCoint)break;
		else if (coint < nextCoint) {
		coint += a;
			}
		else if (coint > nextCoint) {
		coint -= a;
			}
		OCR0A=coint;
		delay(16);
	}
	
}
void S_Change() {
		if (a > (nextCoint - coint))a = 1;//if (a > (nextCoint - coint)&&status==0)a = 1;
		//if (coint == nextCoint)status = 1;
		else if (coint < nextCoint) {
			coint += a;
			//status = 0;
		}
		else if (coint > nextCoint) {
			coint -= a;
			//status = 0;
		}
		OCR0A=coint;
	}
#endif /* PWM_H_ */