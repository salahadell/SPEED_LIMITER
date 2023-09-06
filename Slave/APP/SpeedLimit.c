/*
 * SpeedLimit.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Shawky
 */
#define F_CPU 16000000UL

#include "util/delay.h"
#include "lcd.h"
#include "external_eeprom.h"
#include "twi.h"
#include "spi.h"
uint8 data = 0;
uint8 saved_data = 0;

int main(void)
{
	
	SPI_initSlave();
    TWI_init();
	while(1)
	{
		data = SPI_sendReceiveByte(saved_data);
		/*if(BIT_IS_SET(data,7))
		{
			CLEAR_BIT(data,7);
			EEPROM_writeByte(0x0311,data);
			_delay_ms(10);
		}*/
		/*if(data==80||data==90||data==120)
		{
            EEPROM_writeByte(0x0311,data);
			_delay_ms(10);
			EEPROM_readByte(0x0311,&saved_data);
			_delay_ms(10);

		}*/
		/*else
		{
			SPI_sendReceiveByte(saved_data);
		}
		EEPROM_readByte(0x0311,&saved_data);*/

		switch(data)
		{
			case 80:
			case 90:
			case 120:
				 EEPROM_writeByte(0x0311,data);
				// _delay_ms(10);
				//EEPROM_readByte(0x0311,&saved_data);
				 break;
			case 0:
				//SPI_sendReceiveByte(saved_data);
			break;
			default:
				EEPROM_readByte(0x0311,&saved_data);
				SPI_sendReceiveByte(saved_data);
				break;
		}
	}
}
