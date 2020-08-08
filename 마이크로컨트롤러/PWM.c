#include<avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x) (unsigned int)(16000000/(2*8*(1+x)))
#include <util/delay.h>
#include<avr/interrupt.h>
unsigned int note_freq[7] = {2093,2349,2637,2794,3136,3520,3951};
unsigned char led_array_PD[7] = {0x10,0x30,0x70,0xF0,0xF0,0xF0,0xF0};
unsigned char led_array_PB[7] = {0x00,0x00,0x00,0x00,0x01,0x03,0x07};
#define	ON	1
#define	OFF	0

int on_off = 0;
int note = 0;

void stop(void)
{
   TCCR1A = 0x00;
   TCCR1B = 0x00;
   TCNT1 = 0;
   ICR1 = 0;
   DDRB = ~0X02;
}

void play(unsigned int y)
{
   unsigned int x;
   DDRB |= 0X02;
   TCCR1A |= 0x40;
   TCCR1B |= 0x1A;
   y = FREQ(note_freq[y%7]);
   ICR1 = y;
}
ISR (INT0_vect)
{
	cli();
	_delay_ms(200);
	note++;
	if(note>6){
	note = 6;
	}
	PORTD = ~(led_array_PD[note]) &0xF0;;
	PORTC = ~(led_array_PB[note]) & 0x0F;
	EIFR |= 0x01; 
	sei();
}
ISR (INT1_vect)
{
	cli();
	_delay_ms(200);
	note--;
	if(note <0){
	note = 0;
	}
	PORTD = ~(led_array_PD[note]);
	PORTC = ~(led_array_PB[note]);
	EIFR |= 0x02; 
	sei();
}


int main()
{
	cli();
	DDRD = 0XF3;
	DDRB = 0x0F; // 하위 4비트 활성화
 	DDRC = 0x0F;
 	PORTD = 0x00;
    PORTB = 0x00;
	EICRA = 0x0A; 	
	// Falling Edge Triger
 	EIMSK = 0x03; 	
	// interrupt enable
	EIFR |= 0x03; 

	sei();
	stop();
	note=5;
	PORTD = ~(led_array_PD[note]);
	PORTC = ~(led_array_PB[note]);
	int dic=0;
	while(1)
	{
		if (PIND&0x04)
		{
			_delay_ms(20);
			while(PIND&0x04)
			{
				if (PIND&0x08)
				{
					dic=1;
				}
			}
		}
		else if (PIND&0x08)
		{
			_delay_ms(20);
			while(PIND&0x08)
			{
				
				if (PIND&0x04)
				{
					dic=0;
				}
			}
		}
		if (dic==1)
		{
			play(note);
		}
		else
		{
			stop();
		}
	}
}
