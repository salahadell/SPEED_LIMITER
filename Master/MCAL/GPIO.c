/*
 * GPIO.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Shawky
 */

#include <avr/io.h>
#include "GPIO.h"


void DIO_SetPortDir(uint8 PORT_ID,uint8 direction)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		DDRA = 	direction;						break;
	case DIO_PORTB:
		DDRB = 	direction;						break;
	case DIO_PORTC:
		DDRC = 	direction;						break;
	case DIO_PORTD:
		DDRD = 	direction;						break;
	default:									break;
	}
}

void DIO_SetPinDir(uint8 PORT_ID,uint8 PIN_ID,uint8 direction)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		if(direction == DIO_PIN_HIGH)
		{
			SET_BIT(DDRA,PIN_ID);
		}
		else
		{
			CLEAR_BIT(DDRA,PIN_ID);
		}
		break;
	case DIO_PORTB:
		if(direction == DIO_PIN_HIGH)
		{
			SET_BIT(DDRB,PIN_ID);
		}
		else
		{
			CLEAR_BIT(DDRB,PIN_ID);
		}
		break;
	case DIO_PORTC:
		if(direction == DIO_PIN_HIGH)
		{
			SET_BIT(DDRC,PIN_ID);
		}
		else
		{
			CLEAR_BIT(DDRC,PIN_ID);
		}
		break;
	case DIO_PORTD:
		if(direction == DIO_PIN_HIGH)
		{
			SET_BIT(DDRD,PIN_ID);
		}
		else
		{
			CLEAR_BIT(DDRD,PIN_ID);
		}
		break;
	default:									break;
	}
}

void DIO_SetPortVal(uint8 PORT_ID,uint8 value)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		PORTA = value;					 		break;
	case DIO_PORTB:
		PORTB = value;					 		break;
	case DIO_PORTC:
		PORTC = value;					 		break;
	case DIO_PORTD:
		PORTD = value;					 		break;
	default:									break;
	}
}

void DIO_SetPinVal(uint8 PORT_ID,uint8 PIN_ID,uint8 value)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		if(value == LOGIC_HIGH)
		{
			SET_BIT(PORTA,PIN_ID);
		}
		else
		{
			CLEAR_BIT(PORTA,PIN_ID);
		}
		break;
	case DIO_PORTB:
		if(value == LOGIC_HIGH)
		{
			SET_BIT(PORTB,PIN_ID);
		}
		else
		{
			CLEAR_BIT(PORTB,PIN_ID);
		}
		break;
	case DIO_PORTC:
		if(value == LOGIC_HIGH)
		{
			SET_BIT(PORTC,PIN_ID);
		}
		else
		{
			CLEAR_BIT(PORTC,PIN_ID);
		}
		break;
	case DIO_PORTD:
		if(value == LOGIC_HIGH)
		{
			SET_BIT(PORTD,PIN_ID);
		}
		else
		{
			CLEAR_BIT(PORTD,PIN_ID);
		}
		break;
	default:									break;
	}
}
void DIO_ReadPort(uint8 PORT_ID,uint8* val)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		*val = PINA; 							break;
	case DIO_PORTB:
		*val = PINB; 							break;
	case DIO_PORTC:
		*val = PINC; 							break;
	case DIO_PORTD:
		*val = PIND; 							break;
	default:									break;
	}

}

void DIO_ReadPin(uint8 PORT_ID,uint8 PIN_ID,uint8* val)
{
	switch(PORT_ID)
	{
	case DIO_PORTA:
		*val = GET_BIT(PINA,PIN_ID); 			break;
	case DIO_PORTB:
		*val = GET_BIT(PINB,PIN_ID); 			break;
	case DIO_PORTC:
		*val = GET_BIT(PINC,PIN_ID); 			break;
	case DIO_PORTD:
		*val = GET_BIT(PIND,PIN_ID); 			break;
	default:									break;
	}
}

void DIO_TogglePin(uint8 PORT_ID, uint8 PIN_ID)
{

	switch(PORT_ID)
	{
	case DIO_PORTA:
		TOGGLE_BIT(PORTA,PIN_ID); 				break;
	case DIO_PORTB:
		TOGGLE_BIT(PORTB,PIN_ID); 				break;
	case DIO_PORTC:
		TOGGLE_BIT(PORTC,PIN_ID); 				break;
	case DIO_PORTD:
		TOGGLE_BIT(PORTD,PIN_ID); 				break;
	default:									break;
	}

}



