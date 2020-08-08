#include<avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x) (unsigned int)(16000000/(2*8*(1+x)))
#include <util/delay.h>
#include<avr/interrupt.h>


unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x27,0x7F,0x67,0x77,0x7F,0x39,0x3F,0x79,0x71};
unsigned int GetADCData(uint8_t aIn)
{
	unsigned int result;
	ADMUX = aIn;
	ADCSRA = (1 <<ADEN) | (1 << ADPS2) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	result = ADCL + (ADCH << 8);
	
	_delay_ms(1);
	ADCSRA = 0x00;
	return result;
}

void disp_led(unsigned int i)
{
	if (i<4)
	{
		unsigned char temp=0;
		for (int k=0;k<i;k++)
		{
			temp=temp|(1<<k);
		}
		PORTD=~temp<<4;
		PORTB=0x0F;
	}
	else
	{
		unsigned char temp=0, temp1=0;
		for (int k=0;k<4;k++)
		{
			temp=temp|(1<<k);
		}
		for (int k=0;k<i-4;k++)
		{
			temp1=temp1|(1<<k);
		}
		PORTD=~temp<<4;
		PORTB=~temp1;
	}
}

int main()
{
 	DDRD = 0xF0;
 	DDRB = 0x0F;
 	DDRC = 0x3E;

	while(1){
		unsigned int result=GetADCData(0);
		
		disp_led(result/128+1);
	}
}

//
