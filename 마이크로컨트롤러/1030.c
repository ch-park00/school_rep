/*
   인터럽트 
  프로그램 실행 중에 CPU 의 현재 처리 순서를 중단시키고 다른 동작을 수행하도록 하는 것

  AVR 에서의 인터럽트 처리

  1. 사용할 인터럽트 등록(세팅)
  2. 인터럽트 방식 설정
  3. 해당 인터럽트의 ISR 코딩(CPU가 call 해줌)
  4. Global Interrupt Enalbe


  CPU INT0/INT1 > 인터럽트 받는 곳

  INT1 
  ISC10,11 로 control

  ISR(INT0_vect)  //  외부인터럽트 0번의 ISR
  {				  //  
  cli();
  EIFR |=0x01;
  sei();
  }
*/


#include<avr/interrupt.h>

#include<avr/io.h>			// 기본
#define F_CPU 16000000UL	// 딜레이 쓰기 위함
#include<util/delay.h>



unsigned char seg_tbl16[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
unsigned char seg_tblD[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
void disp_seg (int in);
void LED_shift_dec(int num);


int main()
{

	DDRD = 0xF3;
	DDRB = 0xFF;
	DDRC = 0xFF;
	PORTC = 0xFF;

	unsigned char inc;
	unsigned char shift;
	int num = 0x00;

	while(1){						// 폴링 방식(계속 확인), main 이 커진다(헤비).

		inc = ((PIND & 0X04)>>2);
		shift = ((PIND & 0X08)>>3);		
		num = num + inc;
		
		while(PIND & 0X04){
			if(num==16){
				num = 0x00;
			}
		}
		if(shift == 0X01){
			if(num != 0){
				LED_shift_dec(num);
				num = 0;
			}
		}
		disp_seg(num);
		_delay_ms(100);
	}
}


void disp_seg (int in)
{
	PORTD = (seg_tblD[in]<<4);
	PORTB = (seg_tblD[in]>>4 | 0XF0);
}

void LED_shift_dec(int num)
{
	int max = num;
	for(int i = 0 ; i < max ; i++){
		for(int j = 0 ; j < 8 ; j++){
			PORTD = (seg_tblD[num]<<4);
			PORTB = ~(0x01<<j)<<4 | (seg_tblD[num] >> 4);
			PORTC = ~(0x01<<j)>>2;
			_delay_ms(50);
		}
		for(int j = 0 ; j < 8 ; j++){
			PORTD = (seg_tblD[num]<<4);
			PORTB = ~(0x80>>j)<<4 | (seg_tblD[num] >> 4);
			PORTC = ~(0x80>>j)>>2;
			_delay_ms(50);
		}
		num--;
	}
}
