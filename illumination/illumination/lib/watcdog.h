/*
 * watcdog.h
 *
 * Created: 19.07.2018 18:47:10
 *  Author: MY_PC
 debug status: +
 */ 
 #pragma once

#ifndef WATCDOG_H_
#define WATCDOG_H_
#include <avr/io.h> 

volatile unsigned long int cikle;


	class Interval{
		unsigned long int temp;
		bool f1;
		public:
		bool interval(unsigned int time,  void (*func)(),bool f=1); //���������� ������� ����� ����������� ��������� ������� (��). ������ ���������� � �����
	};

	void delay(unsigned long int time);		//�������� �������� (��)
	void wBegin();							//������������� ����������� �������
	unsigned long int getCicle();			//���������� �����(������� 16) � ������������� � ������ ������� ��������� 
	

//################################################
		
	ISR(WDT_vect)
		{
		cikle+=16;
		}
		
		unsigned long int getCicle(){
		return cikle;} 

	void wBegin(){	
		WDTCR  |= 1 << WDCE;
		WDTCR  |= 0b01000000; // 1 ������������ -- 16 ��
		sei();
		}

	void delay(unsigned long int time){
		unsigned long int t=getCicle();
		while(getCicle()-t<(time));
		return;
		}


bool Interval::interval(unsigned int time, void (*func)(),bool f) {
	if (f) {
		if(f1){
			f1 = 0;
			temp = getCicle();
			func();
			return 1;
		}
		else {
			if (getCicle() - temp >= time)f1 = 1;
			return 0;
		}	
	}
	return 0;
}

#endif /* WATCDOG_H_ */