#define F_CPU 120000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/PWM.h"
#include "lib/ExternalInterupt.h"
#include "lib/watcdog.h"

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

int main()
{
	
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
				//delay(220);
				ledInvert();
			//	delay(220);
				ledInvert();
			//	delay(220);
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
			//	delay(220);
				ledInvert();
			//	delay(220);
				ledInvert();
			//	delay(220);
				ledInvert();
				//
			}
		}
	}
}










		 