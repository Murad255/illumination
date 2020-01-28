/*
 * Blinc.cpp
 *
 * Created: 28.01.2020 22:37:09
 * Author : murad
 */ 
#define F_CPU 1200000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
		DDRB |=1<<0;
		MCUCR|=1<<PUD;
		TCCR0A=0b10000001; //выбираем неинверсный режим шим для обоих светодиодов
		TCCR0B=0b00000001;  //выбираем работу таймера без предделителя тактовой частоты
		
    while (1) 
    {
		for(int n=0;n<256;n++){
			
			OCR0A=n;
			_delay_ms(15);
		}
		_delay_ms(150);
		for(int n=255;n>=0;n--){
			
			OCR0A=n;
			_delay_ms(15);
		}
		_delay_ms(500);
    }
}

