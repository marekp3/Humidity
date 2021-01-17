#include "OW.h"
#include <util\atomic.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <util\atomic.h>


void OW_init()
{
		CLR(DDR, OW_PIN);
		CLR(PORT, OW_PIN);
	
}


uint16_t OW_Read2Byte()
{
	
		int hum,i = 0;
		for(i=0;i<16;i++)
		{
			hum<<=1;
			if(OW_ReadBit()) hum|=0x01;
		}
		return hum;
	
}



uint16_t OW_Read8Bits()

{
	
		uint16_t check = 0;
		int i = 0;
		for(i=0;i<8;i++)

		{
			check<<=1;
			if(OW_ReadBit()) check|=0x01;
		}
		
		return check;
	
}


void OW_ResetPulse()
{
		
		SET(DDR, OW_PIN);
		_delay_us(1000);
		CLR(DDR, OW_PIN);
		_delay_us(40);
	
}
unsigned char counter = 0;

bool OW_WaitForPresencePulse()
{
	
		
		OW_ResetPulse();
			counter=0;
			while((counter<0xFF) && (GET(OW_PIN)!=0))
			{
				_delay_us(1);
				counter++;
			}
		
			if(counter==0xFF)
			{
				return false;
			}
		
			counter=0;
		
			while((counter<0xFF) && (GET(OW_PIN)==0))
			{
				_delay_us(1);
				counter++;
			}
		
		
			if(counter==0xFF)
			{
				return false;
			}
			counter=0;
			while((counter<0xFF) && (GET(OW_PIN)!=0))
			{
				_delay_us(1);
				counter++;
			}
			while(counter==0xFF)
			{
				return false;
			}
	
	

	return true;
}




bool OW_ReadBit()
{
	
		int counter = 0;
		
		while((counter<0xFF) && (GET(OW_PIN)==0))
		{
			counter++;
			_delay_us(1);
		}
		if(counter==0xFF) return false;
		counter = 0;
		
		
		while((counter<0xFF) && (GET(OW_PIN)!=0))
		{
			counter++;
			_delay_us(1);
		}
		if(counter==0xFF)
		{
			return false;
		}
		if((counter <= 0x1D))
		{
			return false;
		}
		if ((counter > 0x1D))
		{
			return true;
		}
		return false;
	
}

