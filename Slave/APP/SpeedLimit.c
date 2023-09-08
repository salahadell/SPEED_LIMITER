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
#include "I2C.h"
#include "spi.h"
uint8 data = 0;
uint8 saved_data = 0;

int main(void)
{
	
	SPI_initSlave();
	/*I2c Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=16Mhz */
    master_init(I2C_STANDARD_SPEED_400K,Prescaler_1);
	while(1)
	{
		data = SPI_sendReceiveByte(saved_data);
		switch(data)
		{
			//if the value equals the speed limiter values then save it
			case 80:
			case 90:
			case 120:
				 EEPROM_writeByte(0x0311,data);
				 break;
			case 0:
				//we call this case after calling the update case using default to read the correct value from the EEPROM
				/*do nothing*/
			break;
			default:
				//update the value before read it
				EEPROM_readByte(0x0311,&saved_data);
				break;
		}
	}
}
