/*
 * speedLimit.c
 *
 *  Created on: Sep 3, 2023
 *      Author: amrfawzy
 */

#include "lcd.h"  /* driver from KL15 project on github */
#include "push_button.h"  /* driver from KL15 project on github */
#include "std_types.h"
#include "Potentiometer.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include "spi.h"

 

#define GEAR_P   0
#define GEAR_R   1
#define GEAR_N   2
#define GEAR_D   3

#define Button_Plus BUTTON4
#define Button_Minus BUTTON3

#define Button_SET_LIMIT     BUTTON2
#define Button_TOGGLE_LIMIT  BUTTON1

uint8 PotentiometerShift = 0;
uint8_t setSpeedFlag = 0;
uint8 speed_limit = 20;

void init(void);
void homePage(void);
void getSpeed(uint8* speed, uint8_t gear , uint8 is_speed_limit_on);
void set_speed_limit();
/*
 *  gear modes
 *  gear = 0 --> P
 *  gear = 1 --> R
 *  gear = 2 --> N
 *  gear = 3 --> D
 */

void set_speed_limit()
{
	uint8 speedlimit=0;
	LCD_Clear();
	_delay_ms(100);
	LCD_GOTO_XY(1,2);
	LCD_WriteString("CHOOSE THE SPEED");
	LCD_GOTO_XY(3,0);
	LCD_WriteString("1) 80        2) 90");
	LCD_GOTO_XY(4,0);
	LCD_WriteString("3) 120       4) back");
	while(1)
	{
		if(ButtonPressed(BUTTON1)==0) /*if button 1 pressed the speed limit is set to 80*/
		{
			while(ButtonPressed(BUTTON1) == 0);
			speedlimit=80;
			break;
		}
		else if (ButtonPressed(BUTTON2)==0) /*if button 2 pressed the speed limit is set to 90*/
		{
			while(ButtonPressed(BUTTON2) == 0);
			speedlimit=90;
			break;
		}
		else if(ButtonPressed(BUTTON3)==0) /*if button 3 pressed the speed limit is set to 120*/
		{
			while(ButtonPressed(BUTTON3) == 0);
			speedlimit=120;
			break;
		}
		else if(ButtonPressed(BUTTON4)==0) /*if button 4 pressed then break */
		{
			while(ButtonPressed(BUTTON4) == 0);
			return;
		}
		else{}
			

	}
	//SET_BIT(speedlimit,7);
	setSpeedFlag = 1;
	SPI_sendReceiveByte(speedlimit);
	LCD_Clear();
}

void getSpeed(uint8* speed, uint8_t gear , uint8 is_speed_limit_on)
{
	if(setSpeedFlag == 1)
        {
        speed_limit = SPI_sendReceiveByte(200);
        _delay_ms(100);
		speed_limit = SPI_sendReceiveByte(0);
		setSpeedFlag = 0;
	}
	*speed = ReadPotentiometer();
	
	if(*speed > PotentiometerShift){
		*speed -= PotentiometerShift;
	}
	else{
		PotentiometerShift = ReadPotentiometer();
		*speed = 0;
	}

	if(*speed > speed_limit && is_speed_limit_on)
	{ 
		*speed = speed_limit ;
		
	}
	if(gear == GEAR_R && *speed > 30){
		*speed = 30;
	}
	LCD_GOTO_XY(1,17);
	LCD_intgerToString(speed_limit);
	LCD_Writechar(' ');
	_delay_ms(10);
}


void getGear(uint8* gear){

	if(ButtonPressed(Button_Plus) == 0){
		while(ButtonPressed(Button_Plus) == 0);

		switch(*gear){
			case 0:
			case 1:
			case 2:
				(*gear)++;
				break;
			case 3:
				break;
			default:
				break;
		}
	}

	else if(ButtonPressed(Button_Minus) == 0){
		while(ButtonPressed(Button_Minus) == 0);

		switch(*gear){
			case 0:
				break;
			case 1:
			case 2:
			case 3:
				(*gear)--;
				break;
			default:
				break;
		}
	}
}

void operation(uint8* speed_limit , uint8* is_speed_limit_on){
	if(ButtonPressed(Button_SET_LIMIT) == 0)
	{
		while(ButtonPressed(Button_SET_LIMIT) == 0);
		set_speed_limit();
	}
	else if(ButtonPressed(Button_TOGGLE_LIMIT) == 0)
	{
		while(ButtonPressed(Button_TOGGLE_LIMIT) == 0);
		if(*is_speed_limit_on == 0){
			*is_speed_limit_on = 1;
		}
		else{
			*is_speed_limit_on = 0;
		}
	}


}

void homePage(void)
{
	uint8 speed = 0 ;
	uint8 gear = 0;
	uint8 is_speed_limit_on = 0 ;
	
	PotentiometerShift = ReadPotentiometer();
	
	while(1)
	{
		getSpeed(&speed, gear , is_speed_limit_on);
		getGear(&gear);
		switch(gear)
		{
			case GEAR_P:
				LCD_GOTO_XY(2,0);
				LCD_WriteString("speed:");
				LCD_intgerToString(0);
				LCD_Writechar(' ');
				LCD_Writechar(' ');
				LCD_GOTO_XY(2,13);
				LCD_WriteString("gear(P)");
				break;
			case GEAR_R:
				LCD_GOTO_XY(2,0);
				LCD_WriteString("speed:");
				LCD_intgerToString(speed);
				LCD_Writechar(' ');
				LCD_Writechar(' ');
				LCD_GOTO_XY(2,13);
				LCD_WriteString("gear(R)");
				break;
			case GEAR_N:
				LCD_GOTO_XY(2,0);
				LCD_WriteString("speed:");
				LCD_intgerToString(0);
				LCD_Writechar(' ');
				LCD_Writechar(' ');
				LCD_GOTO_XY(2,13);
				LCD_WriteString("gear(N)");
				break;
			case GEAR_D:
				LCD_GOTO_XY(2,0);
				LCD_WriteString("speed:");
				LCD_intgerToString(speed);
				LCD_Writechar(' ');
				LCD_Writechar(' ');
				LCD_GOTO_XY(2,13);
				LCD_WriteString("gear(D)");
				break;
		}
		LCD_GOTO_XY(1,0);
		LCD_WriteString("speed limit: ");
		if(is_speed_limit_on == 0)
		{
			LCD_WriteString("OFF");
		}
		else
		{
			LCD_WriteString("ON ");
		}
		LCD_GOTO_XY(3,0);
		LCD_WriteString("1 speed Limit ON/OFF");
		LCD_GOTO_XY(4,0);
		LCD_WriteString("2 set speed limit");
		
		operation(&speed_limit , &is_speed_limit_on);
	}

	
}

void init()
{
	LCD_Init();
	Potentimeter_init();
	SPI_initMaster();
	Set_Button(Button_Plus);
	Set_Button(Button_Minus);
	Set_Button(Button_SET_LIMIT);
	Set_Button(Button_TOGGLE_LIMIT);
}

int main()
{
	init();
	_delay_ms(500);
	LCD_GOTO_XY(2, 4);
	LCD_WriteString("ALPHA TECH");
	_delay_ms(5000);
	LCD_Clear();
	speed_limit = SPI_sendReceiveByte(200);
	  _delay_ms(10);
    speed_limit = SPI_sendReceiveByte(0);
	homePage();
	return 0 ;
}



