/*
 * lcd.h
 *
 *  Created on: Aug 18, 2023
 *      Author: Shawky
 */

#ifndef LCD_H_
#define LCD_H_

#include "lcd_cfg.h"
#include "std_types.h"

void LCD_Init(void);

void LCD_WriteCommand(uint8 cmd);

void LCD_Writechar(uint8 chr);

void LCD_WriteString(const char *str);

void LCD_Clear(void);

void LCD_intgerToString(uint32 number);

void LCD_GOTO_XY(uint32 line,  uint32 position);

#endif /* LCD_H_ */
