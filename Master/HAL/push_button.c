/*
 * Push_Button.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Shawky
 */

#include "GPIO.h"
#include "push_button.h"

void Set_Button(uint8 Button_ID)
{
	switch(Button_ID)
	{
	case 0:
		DIO_SetPinDir(DIO_PORTD,DIO_PIN7,DIO_PIN_INPUT);					break;
	case 1:
		DIO_SetPinDir(DIO_PORTD,DIO_PIN6,DIO_PIN_INPUT);					break;
	case 2:
		DIO_SetPinDir(DIO_PORTD,DIO_PIN5,DIO_PIN_INPUT);					break;
	case 3:
		DIO_SetPinDir(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);					break;
	default:
	break;
	}
}

uint8 ButtonPressed(uint8 Button_ID)
{
	uint8 state = 1;

	switch(Button_ID)
	{
	case 0:
		DIO_ReadPin(DIO_PORTD,DIO_PIN7,&state);								break;
	case 1:
		DIO_ReadPin(DIO_PORTD,DIO_PIN6,&state);								break;
	case 2:
		DIO_ReadPin(DIO_PORTD,DIO_PIN5,&state);								break;
	case 3:
		DIO_ReadPin(DIO_PORTD,DIO_PIN3,&state);								break;
	default:
	break;
	}
	return state;
}
