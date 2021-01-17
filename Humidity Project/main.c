#define F_CPU 8000000UL
#include "OW.h"
#include "OW.c"
#include <avr/io.h>
#include <avr/interrupt.h>
#define  LEDDISPNO 4
#define timer_start 5
volatile bool second_count = true;
volatile uint16_t hum_wart = 0;
volatile uint16_t hum_dz = 0;
volatile uint16_t hum_jed = 0;
volatile uint16_t hum_prec = 0;
volatile uint16_t przerwanie = 0;
volatile uint16_t temp = 0;
volatile uint16_t temp_dz = 0;
volatile uint16_t temp_jed = 0;

volatile uint16_t temp_prec = 0;
volatile uint16_t crc = 0;

int main()
{
	uint16_t check = 0;
	bool OW_READ = false;


	DDRD = 0xFF;
	DDRC |= 0xFF;
	PORTC |=0x0F;
	PORTD = 0xFF;

	TIMSK |= (1<<TOIE0);
	TCCR0 |= (1<<CS01);
	TCNT0 = timer_start;
	sei();
	
	_delay_ms(4000);


    while (1) 
    {
		if(second_count==true)
		{
			
				
			
				second_count = false;
			
				OW_READ=OW_WaitForPresencePulse();
			
				if(OW_READ)
				{
	
					hum_wart = OW_Read2Byte();

					crc = (hum_wart & ~(~0<<8)) + ((hum_wart & (~(~0<<8))<<8)>>8);

					hum_dz=hum_wart/100;
					hum_jed=(hum_wart-(hum_dz*100))/10;
					hum_prec = (hum_wart-(hum_dz*100) - (hum_jed*10));
					temp = OW_Read2Byte();

					crc = crc + (temp & ~(~0<<8)) + ((temp & (~(~0<<8))<<8)>>8);
					temp_dz=temp/100;
					temp_jed=(temp-(temp_dz)*100)/10;
					temp_prec = (temp-(temp_dz*100) - (temp_jed*10));
					check = OW_Read8Bits();
					crc = crc & ~(~0<<8);
					if(crc == check)
					{
					
					}
					else if (crc !=check)
					{
						temp_jed = temp_dz = temp_prec = 2;
					
					}
				
							
			}
			
			//else PORTD = 0x00;
		}

		
		
    }
}

ISR(TIMER0_OVF_vect)
{
	static int licznik, ktory  = 0;
	licznik++;
	ktory++;
	static uint8_t DIGITS[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
	static uint8_t DOT = 0x80;
	static uint8_t LEDNO;
		
	if(licznik==4000)
	{
		second_count = true;
		licznik=0;
	}
	if(ktory==5)
	{
		
		PORTC&=0xF0; //Trun Off All Displays
		LEDNO=(LEDNO+1)%LEDDISPNO; //Modulo daje nam 0,1,2,3
		if(LEDNO==3) PORTD = 0x00; //DIGITS[hum_dz];

		else if(LEDNO==2) PORTD = DIGITS[temp_prec];
		else if(LEDNO==1) PORTD = (DIGITS[temp_jed] | DOT);
		else if(LEDNO==0) PORTD = DIGITS[temp_dz];
		PORTC = PORTC | (1<<LEDNO);
		ktory=0;
		

	}
	
	TCNT0 = timer_start;

		
}

