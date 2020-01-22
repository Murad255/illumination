#define F_CPU 120000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib/PWM.h"
#include "lib/ExternalInterupt.h"
#include "lib/watcdog.h"

//
//	RESET	-## ##- VCC
//			-#####-			SCK
//			-#####- BUTTON	MISO
//		GND	-#####- LED		MOSI
//
/*	��� ������� �� ������ ���������� ���������.
	��� ������� ������� ���������� ����� ��������� �������
	(������� �� ��������� ������� ������� ��� ����������� 
	�������). ����� �� ������ ��������� �� �������� �������
	
*/	
int main()
{
	Led led; 
	wBegin();
	led.PWMbegin();
	ExIntBegin();

	led.ledOff();
	delay(300);
	for(int n=0;n<6;n++){
		led.ledOn(n);
		delay(200);
	}
	led.ledOff();
	
/////////Start///////

	while(1){
		if(availableExInt()){
			delay(220);
			int n=(int)readExInt();
			
			//����������� �������
			if(n==1){
				led.ledInvert(800);
			}
			
			//��� ���������� �������� �����
			else if(n>1){
				led.ledInvert();
				delay(220);
				led.ledInvert();
				delay(220);
				led.ledInvert();
				delay(220);
				led.ledInvert();
				//
				while(1){
					if(availableExInt()){
						delay(220);
						int l=(int)readExInt();
						if(l==1)led.Up();
						else if(l>1)break;
					}
				}
				led.ledInvert();
				delay(220);
				led.ledInvert();
				delay(220);
				led.ledInvert();
				delay(220);
				led.ledInvert();
				//
			}
		}
	}
}










		 