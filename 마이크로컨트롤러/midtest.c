#include<avr/io.h>			// 기본
#define F_CPU 16000000UL	// 딜레이 쓰기 위함
#include<util/delay.h>
#define FOSC 16000000UL

/*
void LED_SECOND_CLASS()
{
	PORTB = 0xFF;
	PORTC = 0xFF;
	int led = 0x00;
	for(int i=0; i<4; i++)
	{
		led = led | (0x02<<(2*i));
		PORTB = ~led;
		PORTC = (~led)>>4;
		_delay_ms(500);
	}
	
	for(int i=0; i<4; i++)
	{
		led = led | (0x01<<(2*i));
		PORTB = ~led;
		PORTC = (~led)>>4;
		_delay_ms(500);
	}
}

int main(void)
{
	DDRB = 0x0F;
	DDRC = 0x0F;

	while(1)
	{
		LED_SECOND_CLASS();
	}
}
*/
/*
unsigned char seg_tblD[] = 
	{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

void Disp_Seg(int num)
{
	int a = num/16;
	int b = num%16;
	PORTD = ((seg_tblD[a]<<2 & 0x1F) | seg_tblD[b]<<5);
	PORTB = ((seg_tblD[a]>>3 & 0X07) | (seg_tblD[b] & 0xF8));
	PORTC = ((seg_tblD[a]>>6 & 0x03) | ((seg_tblD[b]>>4) & 0xFC));
}

int main()
{
	DDRD = 0xFF;
	DDRB = 0x3F;
	DDRC = 0x3F;

	while(1)
	{
		for(int i=0; i<256; i++)
		{
			Disp_Seg(i);
			_delay_ms(500);
		}
	}
}
*/
/*
unsigned char seg_tblD[] = 
	{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79};

	void Disp_Seg(int num)
{
	int a = num/16;
	int b = num%16;
	PORTD = (seg_tblD[a]<<4);
	PORTB = (seg_tblD[a]>>4 | seg_tblD[b]<<4);
	PORTC = (seg_tblD[b]>>2);
}

int main()
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	while(1)
	{
		for(int i=0; i<256; i++)
		{
			Disp_Seg(0x0A/10);
			_delay_ms(500);
		}
	}
}
*/

#include<avr/interrupt.h>	// 인터럽트 서비스

#define INT0_SW 1
#define INT1_SW 2



unsigned char seg_tblD[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
unsigned char in;
int count = 0;

void disp_seg (int a)
{
	PORTD = (seg_tblD[a]<<4) & 0xF0;
	PORTB = ((seg_tblD[a]>>4) & 0x0F) | (PORTB & 0xF0);
}


void LED_shift()
{
	int segb = PORTB;
	for(int j = 0 ; j < 8 ; j++){
		PORTB = ~(0x01<<j)<<4 | (segb & 0x0F);
		PORTC = ~(0x01<<j)>>2;
		_delay_ms(50);
	}
	for(int j = 0 ; j < 8 ; j++){
		PORTB = ~(0x80>>j)<<4 | (segb & 0x0F);
		PORTC = ~(0x80>>j)>>2;
		_delay_ms(50);
	}
}


ISR(INT0_vect) // 외부 인터럽트 0번
{
	cli();
	EIFR |= 0x01;
	count = ++count%10;
	disp_seg(count);
	in = INT0_SW;
	
	sei(); 
}

ISR(INT1_vect) // 외부 인터럽트 1번
{
	cli();
	EIFR |= 0x02;
	in = INT1_SW;
	
	sei(); 
}

int main()
{
	int i;
	
	cli();				// 전체 인터럽트 disable (설정할때는 인터럽트 실행 X)
	DDRD = 0xF3;
	DDRB = 0xFF;
	DDRC = 0xFF;


	EICRA = 0X0F; // sense control (Rising Edge)
	EIMSK = 0X03; // EIMSK 1,2번 비트
	EIFR = 0x03;  // EIFR 1,2번 비트

    sei();				// global interrupt enable (설정 끝 인터럽트 실행)



	while(1){						// 인터럽트 방식
		
		if(in == INT1_SW )// switch 누르면 count up & display
		{
			in = 0;
			for(i = count; i > 0 ; i--) // 현재 count 횟수만큼 shift
			{
				if(in == INT0_SW)
				{
					break;
				}
				if(in == INT1_SW)
				{
					disp_seg(i);
					break;
				}
				LED_shift();
				disp_seg(i-1);
			}
			count = i;
			disp_seg(count);
			in = 0;
		}
	}
}
