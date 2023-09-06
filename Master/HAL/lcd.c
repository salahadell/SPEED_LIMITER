/*
 * lcd.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Salah Adel
 */
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "lcd_cfg.h"
#include "common_macros.h"
#include "lcd.h"
#include "std_types.h"



void LCD_Init(void)
{
	DIO_SetPinDir(LCD_CMD_PORTID,LCD_RS,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_CMD_PORTID,LCD_EN,DIO_PIN_OUTPUT);

	_delay_ms(20);

	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D4,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D5,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D6,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D7,DIO_PIN_OUTPUT);

	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE);


	LCD_WriteCommand(LCD_CURSOR_OFF);
	LCD_WriteCommand(LCD_CLEAR_COMMAND);
	LCD_WriteCommand(0x0F);
}

void LCD_WriteCommand(uint8 cmd)
{
   //MODE OF 4 BITS
   //SET THE RS LOW TO ENABLE COMMAND MODE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_RS,LOGIC_LOW);
	_delay_ms(1);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE MOST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(cmd,4));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(cmd,5));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(cmd,6));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(cmd,7));

   //REFRESHING PULSE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE lEST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(cmd,0));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(cmd,1));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(cmd,2));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(cmd,3));



	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);

}

void LCD_Writechar(uint8 chr)
{
	   //SET THE RS HIGH TO ENABLE DATA MODE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_RS,LOGIC_HIGH);
	_delay_ms(1);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE MOST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(chr,4));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(chr,5));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(chr,6));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(chr,7));

   //REFRESHING PULSE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE lEST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(chr,0));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(chr,1));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(chr,2));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(chr,3));


	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);

}

void LCD_WriteString(const char *str)
{
	uint8 i=0;
	while(str[i] != '\0')
	{
		LCD_Writechar(str[i]);
		i++;
	}
}

void LCD_intgerToString(uint32 number){
	if (number==0)
	{
		LCD_Writechar('0');
		return;
	}
	int n=number;
	uint8 count=0;
	uint8 digit=0;
	for (uint8 i=0;n!=0;i++){
		n=n/10;
		count++;
	}
	uint8 arr[count];
	n=number;
	for (int i=(count-1);i>=0 ;--i){
		digit=n%10;
		digit= digit+'0';
		arr[i]=digit;
		n=n/10;
	}
	for (uint8 i=0;i<count;i++){
		LCD_Writechar(arr[i]);
	}

}
//void LCD_intgerToString(uint32 data)
//{
  // char buff[16]; /* String to hold the ascii result */
   //ltoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   //LCD_WriteString(buff); /* Display the string */
//}


void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_GOTO_XY(uint32 line,  uint32 position){
	if (line == 1)
	{
		if ((position < 20) && (position >= 0)) //MAKING SURE THAT THE POSITION IS IN THE AVALABLE 20 CHAR RANGE
		{
			LCD_WriteCommand(LCD_BEGIN_AT_FIRST_ROW+position); //MOVE THE CURSOR TO THE DESSIRED POSITION
		}
		else{
			/*ERROR*/
		}
	}
	else if (line == 2)
	{
		if ((position < 20) && (position >= 0))
		{
			LCD_WriteCommand(LCD_BEGIN_AT_SECOND_ROW+position);
		}
		else{
			/*ERROR*/
		}
	}
	else if (line == 3)
	{
		if ((position < 20) && (position >= 0))
		{
			LCD_WriteCommand(LCD_BEGIN_AT_THIRD_ROW+position);
		}
		else{
			/*ERROR*/
		}
	}
	else if (line == 4)
	{
		if ((position < 20) && (position >= 0))
		{
			LCD_WriteCommand(LCD_BEGIN_AT_FOURTH_ROW+position);
		}
		else{
			/*ERROR*/
		}
	}
	else{	/*ERROR*/}
}


