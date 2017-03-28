#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int counter = 0;
volatile int b_timer = 0;
volatile int r_timer = 0;

ISR(TIMER0_OVF_vect)
{
	counter++;

	if(counter % 61==0) //0.125초 경과
	{
		if(counter >= 488) //1초 경과
		{	counter = 0;	
			r_timer ++;		
		}
		
		b_timer ++;
		
	}
}


int main(void)
{
    while (1) 
    {
		DDRB = 0x01; // PB0 핀을 output mode로 설정
		TIMSK = 0x01; // TIMER0 overflow interrupt 사용 설정
		TCCR0 = 0x03; // prescalar를 64로 설정

		sei(); // 사용 설정한 interrupt를 활성화

		if(r_timer % 2 == 0){ //짝수초마다 실행
			
			if(b_timer %2 == 0) 
			{
				PORTB = 0x01;  
			}
			else 
				PORTB = 0x00;  
		}
		else 
			PORTB = 0x00;
					
    }
}

