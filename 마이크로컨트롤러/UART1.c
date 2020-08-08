#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x) (unsigned int)(16000000/(2*8*(1+x)))
#include <util/delay.h>
#include <avr/interrupt.h>
#define BAUD_9600 103
unsigned int note_freq[7] = {2093,2349,2637,2794,3136,3520,3951};
unsigned char note[7]={'d','f','z','x','c','a','s'};
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
   DDRB |= 0X02;
   TCCR1A |= 0x40;
   TCCR1B |= 0x1A;
   y = FREQ(note_freq[y%7]);
   ICR1 = y;
}
void tx_char(unsigned char txChar)
{
      while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = txChar;
}

unsigned char send_char=0;

void Printf(char *fmt, ...)
{
	va_list 	arg_ptr;
	uint8_t 	i,len;
	char 	sText[128];
		
	/* text buffer */
	for (i = 0; i < 128; i++)
		sText[i] = 0;

	va_start(arg_ptr, fmt);
	vsprintf(sText, fmt, arg_ptr);
	va_end(arg_ptr);

	len = strlen(sText);
	for (i = 0; i < len; i++){
		tx_char(sText[i]);
	}
}

int main()
{
	unsigned char Rx_char=0;
	cli();
	DDRD=0xF0;
	EICRA=0xAA;
	EIMSK=0X0F;
	EIFR|=0X0F;

	UBRR0H=(unsigned char)(BAUD_9600>>8);
	UBRR0L=(unsigned char)(BAUD_9600);
	UCSR0B=(1<<TXEN0)|(1<<RXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);

	sei();
	Printf("init ok\n");
	while(1)
	{
		unsigned char idx=0;
	//데이터 수신
		while(!(UCSR0A&(1<<RXC0)));
		Rx_char=UDR0;
	//데이터 발신
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0=Rx_char;
		
		for (idx=0;idx<7;idx++)
		{
			if (note[idx]==Rx_char)
			{
				break;
			}
		}
		if (idx==7)
		{
			Printf("error\n");
		}
		else
		{
			play(idx);
			idx=0;
		}
	}
	return 0;
}
