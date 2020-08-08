#include <avr/io.h>
#define FOS 16000000UL
#define F_CPU 16000000UL
#include <util/delay.h>

int main()
{
	DDRD=0xF0;
	DDRB=0x3F;
	DDRC=0x3F;
	unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x27,0x7F,0x67};
	while(1)
	{
		for (int i=0;i<99;i++)
		{
			PORTD=(seg[i/10]&0x0F)<<4;
			PORTB=(((seg[i/10]&0xF0)>>4)|(seg[i%10]&0x03)<<4);
			PORTC=(seg[i%10]&0xFC)>>2;
			_delay_ms(250);
		}
		for (int i=99;i>0;i--)
		{
			PORTD=(seg[i/10]&0x0F)<<4;
			PORTB=(((seg[i/10]&0xF0)>>4)|(seg[i%10]&0x03)<<4);
			PORTC=(seg[i%10]&0xFC)>>2;
			_delay_ms(250);
		}
	}

	return 0;

}
