#define F_CPU 120000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/PWM.h"
#include "lib/ExternalInterupt.h"
#include "lib/watcdog.h"
#include "lib/Smoother.h"

//
//			-## ##- VCC
//			-#####- 
//			-#####- BUTTON
//		GND	-#####- LED
//
/*	при нажатии на кнопку включаетс€ светодиод.
	при двойном нажатии включаетс€ режим настройки €ркости
	(переход на следующий уровень €ркости при однократном 
	нажатии). выход из режима настройки по двойному нажатию
	
*/	

class LedS:public Smoother{
	void Change(){
		OCR0A=coint;
	}
	
	
	public :
	void Up(){
		if(i>4){
			ledOff();
			i=0;
		}
		else{
			 On(++i);
			 
		}
		return;
	}
	void On(byte bright=i){
		f=1;
		i=bright;
		begin(bright*51-51,bright*51);
		
		while (CointNum())delay(1);
	
		return;
	}
	void Invert(){
		
		if(f==0)On();
		else if(f==1)ledOff();
		return;
	}
	};
	
LedS led;
int main()
{
	//LedS led;
	wBegin();
	PWMbegin();
	ExIntBegin();

	ledOff();
	delay(300);
	for(int n=0;n<6;n++){
		ledOn(n);
		delay(200);
	}
	ledOff();


	while(1){
		if(availableExInt()){
			delay(220);
			int n=(int)readExInt();
			if(n==1){
				ledInvert();
			}
			else if(n>1){
				ledInvert();
				delay(220);
				ledInvert();
				delay(220);
				ledInvert();
				delay(220);
				ledInvert();
				//
				while(1){
					if(availableExInt()){
						delay(220);
						int l=(int)readExInt();
						if(l==1)Up();
						else if(l>1)break;
					}
				}
				ledInvert();
				delay(220);
				ledInvert();
				delay(220);
				ledInvert();
				delay(220);
				ledInvert();
				//
			}
		}
	}
}










		 