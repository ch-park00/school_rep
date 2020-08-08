#include<stdio.h>
#include<avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x) (unsigned int)(16000000/(2*8*(1+x)))
#include <util/delay.h>
#include<avr/interrupt.h>
#define BAUD_9600  103
#define MAX_BUFF_SIZE 128
#define LED_ONOFF 0x01
#define LED_ALT 0x02
#define LED_SHIFT 0x04
#define SEG_UP 0x08
#define BUZ 0x10
#define STX 0x02
#define ETX 0x03

#define BUZ_ON 0x01
#define BUZ_OFF 0x00
//function decision
uint8_t fun=0;
//function input
uint8_t input=0;
int decode =0;
uint8_t command=0;
int sint_flag=0;
unsigned char seg_cnt=0;
//function
void LED_ALL_ON_OFF(int cnt);
void LED_ALTERNATING(int cnt);
void LED_Shift(int cnt);

unsigned char seg[] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x27,0x7F,0x67 };

void disp_seg(int i)
{
	PORTC=(PORTC&0x0F)|((seg[i]&0x03)<<4);
	PORTD=(PORTD&0xF0)|((seg[i]&0x0C));
	PORTB=(seg[i]&0xF0)>>2;
	_delay_ms(100);
}
void tx_char(unsigned char txChar)
{
 while (!(UCSR0A & (1 << UDRE0)));
 UDR0 = txChar;
}

void tx_str(unsigned char *txStr, int len)
{
 int i;
 for (i = 0; i < len; i++){
  tx_char(txStr[i]);
 }
}

void stop(void)
{
   TCCR1A = 0x00;
   TCCR1B = 0x00;
   TCNT1 = 0;
   ICR1 = 0;
   DDRB=DDRB&0xFD;
}

void play()
{
   unsigned int x;
   DDRB=DDRB|0x02;
   TCCR1A |= 0x40;
   TCCR1B |= 0x1A;
   x = FREQ(1000);
   ICR1 = x;
}


void Printf(char *fmt, ...)
{
 va_list arg_ptr;
 uint8_t i, len;
 char sText[128];

 /*text buffer*/
 for (i = 0; i < 128; i++) sText[i] = 0;

 va_start(arg_ptr, fmt);
 vsprintf(sText, fmt, arg_ptr);
 va_end(arg_ptr);

 len = strlen(sText);
 for (i = 0; i < len; i++){
  tx_char(sText[i]);
 }
}


ISR(USART_RX_vect){
 unsigned char rcv = 0;
    rcv = UDR0;
    if (decode==0 && rcv==STX)
	{
		decode=1;
	}
	else if (decode==1)
	{
		int temp=-1;
		for (int i=0;i<5;i++)
		{
			if (rcv==(0x01<<i))
			{
				temp=i;
			}
		}
		if (temp==-1)
		{
			Printf("function input error\n");
			decode=0;
		}
		else
		{
			fun=0x01<<temp;
			decode=2;
		}
	}
	else if (decode==2)
	{
		input=rcv;
		decode=3;
	}
	else if(decode==3)
	{
		if (rcv==ETX)
		{
			sint_flag=1;
		}
		else
		{
			Printf("ETX error\n");
		}
		decode=0;
	}
	sei();
}

void Command(uint8_t command,uint8_t input)
{
	if (command==LED_ONOFF)
	{
		LED_ALL_ON_OFF((int)input);
		Printf("LED_ONOFF\n");
	}
	else if (command==LED_ALT)
	{
		LED_ALTERNATING((int)input);
		Printf("LED_ALT\n");
	}
	else if (command==LED_SHIFT)
	{
		LED_Shift((int)input);
		Printf("LED_SHIFT\n");
	}
	else if (command==SEG_UP)
	{	
		for (int k=0;k<(int)input;k++)
		{
			for (int i=0;i<10;i++)
			{
				disp_seg(i);
			}
		}
		Printf("SEG_UP\n");
	}
	else if (command==BUZ)
	{
		if (input==BUZ_ON)
		{
			play();
			Printf("BUZ on\n");
		}
		else if (input==BUZ_OFF)
		{
			stop();
			Printf("BUZ off\n");
		}
		else
		{
			Printf("buzzer input error\n");
			return;
		}
		
	}
}
int main(void)
{

 cli();
 UBRR0H = (unsigned char) (BAUD_9600 >>8) ;
 UBRR0L = (unsigned char) BAUD_9600;
 UCSR0A = 0X00;
 UCSR0B = (1<< TXEN0)|  (1<< RXEN0); 
 UCSR0B |=   (1<< RXCIE0);
 UCSR0C = (1<< UCSZ01) | (1<< UCSZ00);
 sei();
DDRD=0xFF;
DDRB=0x3C;
DDRC=0x3F;
 Printf("\n**************************************\n");
 Printf(" Ready to performance\n");
 Printf("CLK's F is 16000000\n");
 Printf("**************************************\n");
 _delay_ms(500);
 Printf("Let's get it started.\n");

 PORTD=0x00;
 while (1){
 	if (sint_flag)
	{
		Command(fun,input);
		fun=input=0;
		sint_flag=0;
	}
  }

}


void LED_ALL_ON_OFF(int cnt)
{
	for (int i=0;i<cnt;i++)
	{
		PORTD=(PORTD&0x0C);
		PORTC=(PORTC&0x30);
		_delay_ms(200);
		PORTD=(PORTD&0x0C)|0xF0;
		PORTC=(PORTC&0x30)|0x0F;
		_delay_ms(200);
	}
}
void LED_ALTERNATING(int cnt)
{
	for (int i=0;i<cnt;i++)
	{
		unsigned char temp=0x55;
		PORTD=(PORTD&0x0C)|((temp&0x0F)<<4);
		PORTC=(PORTC&0x30)|((temp&0xF0)>>4);
		_delay_ms(200);
		PORTD=(PORTD&0x0C)|((~temp&0x0F)<<4);
		PORTC=(PORTC&0x30)|((~temp&0xF0)>>4);
		_delay_ms(200);
	}
}

void LED_Shift(int cnt)
{
	for (int i=0;i<cnt;i++)
	{
		for (int k=0;k<8;k++)
		{	
			if (k<4)
			{
				PORTD=(PORTD&0x0C)|((~(0x01<<k)&0x0F)<<4);
				PORTC=(PORTC&0x30)|0x0F;
			}
			else
			{
				PORTC=(PORTC&0x30)|~(0x01<<(k-4)&0x0F);
				PORTD=(PORTD&0x0C)|0xF0;
			}
			_delay_ms(100);
		}
		for (int k=7;k>=0;k--)
		{
			if (k>3)
			{
				
				PORTC=(PORTC&0x30)|~(0x01<<(k-4)&0x0F);
				PORTD=(PORTD&0x0C)|0xF0;
			}
			else
			{
				PORTD=(PORTD&0x0C)|((~(0x01<<k)&0x0F)<<4);
				PORTC=(PORTC&0x30)|0x0F;
			
				
			}
			_delay_ms(100);
		}
	}
}


