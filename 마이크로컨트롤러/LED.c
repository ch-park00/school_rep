#include <avr/io.h>
#define FOS 16000000UL
#define F_CPU 16000000UL
#include <util/delay.h>

void LED_ALL_ON_OFF(unsigned int cnt,unsigned int t)
{
	for (int i=0;i<cnt;i++)
	{
		PORTD=0x0F;
		PORTB=0xF0;
		_delay_ms(t);
		PORTD=0xF0;
		PORTB=0x0F;
		_delay_ms(t);
	}
}
void LED_ALTERNATING(unsigned int v,unsigned int cnt,unsigned int t)
{
	if (v>0xFF)
	{
		return;
	}
	for (int i=0;i<cnt;i++)
	{
		int temp=v&0x0F;
		int temp1=v&0xF0;
		PORTD=~temp<<4;
		PORTB=~temp1>>4;
		_delay_ms(t);
		PORTD=temp<<4;
		PORTB=temp1>>4;
		_delay_ms(t);
	}
}
void LED_SHIFT(unsigned int cnt,unsigned int t)
{
	for (int i=0;i<cnt;i++)
	{
		for (int j=0;j<8;j++)
		{
			if (j<4)
			{
				PORTB=0xFF;
				PORTD=~(0x10<<j);
				_delay_ms(t);
			}
			else
			{
				PORTD=0xFF;
				PORTB=~(0x01<<(j-4));
				_delay_ms(t);
			}
		}
		for (int j=1;j<7;j++)
		{
			if (j<4)
			{
				PORTD=0xFF;
				PORTB=~(0x08>>j);
				_delay_ms(t);
			}
			else
			{
				PORTB=0xFF;
				PORTD=~(0x80>>(j-4));
				_delay_ms(t);
			}
		}
	}
	PORTD=~(0x80)>>3;
	_delay_ms(t);
}
int main()
{
	DDRD=0xF0;
	DDRB=0x0F;
	while(1) {
	LED_ALL_ON_OFF(3,500);
	LED_ALTERNATING(0x31,3,500); 
	LED_SHIFT(5,100);
	}
	return 0;
}
