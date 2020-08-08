#include<stdio.h>
#include<avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x) (unsigned int)(16000000/(2*8*(1+x)))
#include <util/delay.h>
#include<avr/interrupt.h>
#define MAX_BUFF_SIZE 128
#define BAUD_9600 103
#define BAUD_38400 25
#define SW1 0x01
#define SW2 0x10
#define STX 0x02
#define ETX 0x03
#define calc 0x01
#define ADC_CON 0x02
#define BUZ_CON 0x03

unsigned int note_freq[7] = {2093,2349,2637,2794,3136,3520,3951};
char sym[]={'+','-','*','/'};
int TovVal=0;
int Tov=0;
int t_flag=0;
int t_flag1=0;
int t_flag2=0;
int decode=0;
unsigned char command=0;
unsigned char len=0;
int sym_dec=0x10;
unsigned char op1=0;
unsigned char op2=0;
unsigned int result=0;
unsigned char adc=0;
unsigned char buz_com=0;
unsigned char cur_p=0;
int buz_dec=0;
int adc_dec=0;
unsigned char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x27,0x7F,0x67,0x77,0x7F,0x39,0x3F,0x79,0x71};
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
void disp_seg(int i)
{
	PORTD=((seg[i]&0x0F)<<4);
	PORTB=(PORTB&0x01)|(((seg[i]&0xF0)>>2)&0x3C);
	
}
void disp_segdot(int i)
{
	PORTD=((seg[i]&0x0F)<<4);
	PORTB=(PORTB&0x01)|(((seg[i]&0xF0)>>2)&0x3C);
	PORTB|=(0x20);
}



void tx_char(unsigned char txChar)
{
      while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = txChar;
}
void stop_timer()
{
	TCCR1B=0x00;
	sei();
}
void start_timer()
{
	cli();

	TCCR1B|=(1<<CS12);
	
	TCCR1B|=(1<<CS10);

	sei();
}
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
ISR(USART_RX_vect){
 unsigned char rcv = 0;
    rcv = UDR0;
    if (decode==0 && rcv==STX)
	{
		decode=1;
	}
	else if (decode==1)
	{
		len=rcv;
		decode=2;
		len--;
	}
	else if (decode==2)
	{
		command=rcv;
		len--;
		decode=3;
	}
	else 
	{
		if (len==0)
		{
			if (command==calc)
			{
				if (sym_dec==0)
				{
					result=op1+op2;
					Printf("%d\n",result);
					start_timer();
				}
				else if (sym_dec==1)
				{
					result=op1-op2;
					start_timer();
				}
				else if (sym_dec==2)
				{
					result=op1*op2;
					start_timer();
				}
				else if (sym_dec==3)
				{
					result=op1/op2;
					start_timer();
				}
				else
				{
					result=0;
					stop_timer();
					Tov=0;
					t_flag1=0;
				}
				decode=0;
				op1=0;
				op2=0;
				len=0;
				sym_dec=0x10;
			}
			else if (command==ADC_CON)
			{
				if (adc==0x08)
				{
					adc=0;
					adc_dec=1;
					start_timer();
					decode=0;
				}
				else
				{
					decode=0;
					adc=0;
					adc_dec=0;
				}
			}
			else if (command==BUZ_CON)
			{
				if (buz_com==0x10)
				{
					buz_dec=1;
				}
				else if (buz_com==0x20)
				{
					buz_dec=0;
					stop();
				}
				else if (buz_com==0x40)
				{
					
					cur_p=(cur_p+1)%7;

				}
				else 
				{
					if (cur_p!=0)
					{
						cur_p=cur_p-1;

					}
					play(cur_p);
					
				}
				decode=0;
				buz_com=0;
			}
		}
		else
		{
			if (command==calc)
			{
				if (len==3)
				{
					for (int i=0;i<4;i++)
					{
						if (rcv==i+1)
						{
							sym_dec=i;
						}
					}
				}
				else if (len==2)
				{
					op1=rcv;
				}
				else
				{
					op2=rcv;
				}
			}
			else if (command==ADC_CON)
			{
				adc=rcv;
			}
			else if (command==BUZ_CON)
			{
				buz_com=rcv;
			}
			len--;
			
		}
	}
	sei();
}
ISR(TIMER0_OVF_vect)
{
	cli();
	TCNT0=0xFF-0x4E;
	TovVal++;

	if (TovVal==40)
	{
		t_flag=1;
		TovVal=0;
	}
	sei();
}
ISR(TIMER1_OVF_vect)
{
	cli();
	TCNT1=0xFFFF-0x004E;
	Tov++;
	
	
	if (result!=0)
	{
		if (Tov==60)
		{
		Tov=0;
		t_flag1=1;
		}
	}
	else
	{
		if (Tov==100)
		{
			Tov=0;
			t_flag1=1;
		}
	}
	sei();
}
int main()
{
	DDRD=0xF0;
	DDRB=0xFD;
	DDRC=0x3F;
	cli();
	EICRA = 0x0F;	// sense control (Rising Edge)
   	EIMSK = 0x03;               //EIMSK 1,2¹øºñÆ®SET
	EIFR = 0x03; 
	UBRR0H=(unsigned char)(BAUD_38400>>8);
	UBRR0L=(unsigned char)(BAUD_38400);
	UCSR0B=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
	
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00)|(USBS0);
	TCCR0A=0x00;
	TCCR0B=0x00;
	
	TCCR1A=0x00;

	TCCR1B=0x00;

	TCNT1=0xFFFF-0x004E;

	TIMSK1|=1<<TOIE1;

	TIFR1|=1<<TOV1;
	TCNT0=0xFF-0x4E;

	TIMSK0|=1<<TOIE0;

	TIFR0|=1<<TOV0;
	Printf("201401653_ParkchulHee\n");
	sei();
	int dec=0;
	int first=0;
	int adc_tim=0;
	while(1)
	{
		
		for (int i=0;i<6;i++)
		{
		if (i==0)
		{
			PORTB=PORTB&~(0x01);
			PORTC=~(0x01<<i+1);
		}
		else if (i<=4)
		{
			PORTC=~(0x01<<(i+1));
			PORTC=PORTC&(~(0x20>>(i-1)));
			PORTB|=0x01;
		}
		else
		{
			PORTB=PORTB&~(0x01);
			PORTC=~(0x20>>(i-1));
		}
		
		TCCR0B|=(1<<CS02);
		TCCR0B|=(1<<CS00);
		
		
		while(t_flag==0)
		{
			if (PIND&0x04)
			{
				_delay_ms(10);
				if (PIND&0x08)
				{	
					tx_char(0x02);
					tx_char(0x03);
					tx_char(0x08);
					tx_char(0xFF);
					tx_char(0x03);
				}
			}
			if (adc_dec)
			{
				
				if (t_flag1)
				{
					unsigned int temp=GetADCData(0);
					Printf("%d\n",temp);
					adc_tim++;
					t_flag1=0;
				}
				
				if (adc_tim==20)
				{
					stop_timer();
					adc_tim=0;
					adc_dec=0;
					Tov=0;
				}
			}
			if (result!=0)
			{
				if (t_flag1)
				{
					if (dec==0)
					{
						dec=1;
					}
					else
					{
						dec=0;
					}
					t_flag1=0;
				}
				if (dec==0)
				{
					disp_segdot(result/16);
				}
				else 
				{
					disp_seg(result%16);
				}
			}
			else
			{
				dec=0;
				first=0;
				disp_seg(0);
			}
			if (buz_dec)
			{
				play(cur_p);
			}
			
		
		}
		
		t_flag=0;
	}
	
	
	}
}
