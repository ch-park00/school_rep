#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include<avr/interrupt.h>

#define INT0_SW  1
#define INT1_SW  2

unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x27,0x7F,0x67};
int count=0;
unsigned char in;
void disp_seg(int i);
void LED_ALL_ON_OFF(int cnt,int t);

ISR(INT0_vect)	// 외부인터럽트 0번의 ISR
{
   cli();		// clear Interrupt
   EIFR |= 0x01; 	// Interrupt Flag set
   count = (count+1)%4;
   EICRA=(count)|((count)<<2);
   disp_seg(count);	
   _delay_ms(150);
   in = INT0_SW;
    sei();		// set interrupt	
}


ISR(INT1_vect)    // 외부인터럽트 1번의 ISR
{
 cli();
 EIFR |= 0x02; 
 in = INT1_SW;
 sei();

}

int main()
{

	cli();

	DDRC = 0x3F;
  	DDRD = 0xF3;
  	DDRB = 0x3F;
	PORTC = 0x3F;
	PORTB = 0x30;

	EICRA = 0x00;	// sense control (Rising Edge)
   	EIMSK = 0x03;               //EIMSK 1,2번비트SET
	EIFR = 0x03;                //EIFR 1, 2번비트SET
	
	sei();		//global interrupt enable
	// Refer to the upper box}
	while(1)
	{
		if (in==INT1_SW)
		{
			int temp=0;
			in=0;
			while (temp<10)
			{ 
				if (in==INT0_SW)
				{
					break;
				}
				if (in==INT1_SW)
				{
					break;
				}
				temp++;
				
				LED_ALL_ON_OFF(1,200);
			}
			in=0;
		}
	}
	return 0;

}

void disp_seg(int i)
{
	PORTD=(seg[i]&0x0F)<<4;
	PORTB=(seg[i]&0xF0)>>4|(PORTB&0x30);
}
void LED_ALL_ON_OFF(int cnt,int t)
{
	for (int i=0;i<cnt;i++)
	{
		PORTB=0x30|(PORTB&0x0F);
		PORTC=0x3F;
		_delay_ms(t);
		PORTB=(PORTB&0x0F)|0xC0;
		PORTC=0xC0;
		_delay_ms(t);
	}
}
