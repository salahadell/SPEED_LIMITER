/*
 * GPIO.H
 *
 *  Created on: Aug 17, 2023
 *      Author: Shawky
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"
#include "common_macros.h"
#include "atmega32_register.h"

#define DIO_PORTA				0
#define DIO_PORTB				1
#define DIO_PORTC				2
#define DIO_PORTD				3

#define DIO_PIN0				0
#define DIO_PIN1				1
#define DIO_PIN2				2
#define DIO_PIN3				3
#define DIO_PIN4				4
#define DIO_PIN5				5
#define DIO_PIN6				6
#define DIO_PIN7				7

#define DIO_PIN_OUTPUT			1
#define DIO_PIN_INPUT			0

#define DIO_PORT_OUTPUT			0XFF
#define DIO_PORT_INPUT			0X00

#define DIO_PIN_HIGH			1
#define DIO_PIN_LOW				0

#define DIO_PORT_HIGH			0XFF
#define DIO_PORT_LOW			0X00

void DIO_SetPortDir(uint8 PORT_ID,uint8 direction);
void DIO_SetPinDir(uint8 PORT_ID,uint8 PIN_ID,uint8 direction);
void DIO_SetPortVal(uint8 PORT_ID,uint8 value);
void DIO_SetPinVal(uint8 PORT_ID,uint8 PIN_ID,uint8 value);
void DIO_ReadPort(uint8 PORT_ID,uint8* val);
uint8 DIO_ReadPin(uint8 PORT_ID,uint8 PIN_ID);
void DIO_TogglePin(uint8 PORT_ID, uint8 PIN_ID);



#endif /* GPIO_H_ */
