/*
 * Push_Button.h
 *
 *  Created on: Aug 20, 2023
 *      Author:Omar Shawky
 */

#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

#include "common_macros.h"
#include "std_types.h"

#define BUTTON1					0
#define BUTTON2					1
#define BUTTON3					2
#define BUTTON4					3

#define BUTTONRELEASED			1
#define BUTTONPRESSED			0


void Set_Button(uint8 Button_ID);

uint8 ButtonPressed(uint8 Button_ID);


#endif /* PUSH_BUTTON_H_ */
