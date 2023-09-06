/*
 * Potentiometer.h
 *
 * Created: 8/26/2023 3:21:11 PM
 *  Author: Lenovo
 */ 


#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include <avr/io.h>
#include "ADC.h"
#include "GPIO.h"

void Potentimeter_init();
uint8_t ReadPotentiometer();

#endif /* POTENTIOMETER_H_ */
