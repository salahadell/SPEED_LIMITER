/*
 * lcd_cfg.h
 *
 *  Created on: Aug 18, 2023
 *      Author: Shawky
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "GPIO.h"

#define LCD_MODE			4

#define	LCD_CMD_PORTID		DIO_PORTA
#define LCD_DATA_PORTID		DIO_PORTB

#define	LCD_D4				DIO_PIN0
#define	LCD_D5				DIO_PIN1
#define	LCD_D6				DIO_PIN2
#define	LCD_D7				DIO_PIN4

#define LCD_RS				DIO_PIN3
#define LCD_EN				DIO_PIN2

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_BEGIN_AT_FIRST_ROW			 	 0x80
#define LCD_BEGIN_AT_SECOND_ROW				 0xc0
#define LCD_BEGIN_AT_THIRD_ROW				 0x94
#define LCD_BEGIN_AT_FOURTH_ROW				 0xD4


#endif /* LCD_CFG_H_ */
