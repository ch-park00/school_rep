#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include<avr/interrupt.h>

void LED_BLINK()
{
	PORTD=0x00;
	_delay_ms(300);
	PORTD=0xFF;
}
ISR(TIMER1_OVF_vect)
{

	LED_BLINK();
	TCNT1=0xFFFF-0x3D09;
	sei();
}
int main()
{
	cli();
	DDRD=0xFF;
	PORTD=0xFF;

	TCCR1A=0x00;

	TCCR1B|=(1<<CS12);
	
	TCCR1B|=(1<<CS10);

	
	TCNT1=0xFFFF-0x3D09;

	TIMSK1|=(1<<TOIE1);

	TIFR1|=(1<<TOV1);

	sei();
	while(1)
	{
	}
	return 0;
}
