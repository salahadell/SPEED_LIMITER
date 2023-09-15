/*
 * ADC.c
 *
 * Created: 8/24/2023 11:14:10 AM
 *  Author: Lenovo
 */ 

#include <avr/io.h>
#include "ADC.h"

/*====================================================================*/
/*							Global Variables                          */
/*====================================================================*/
ADC_Config_t Global_ADC_Config;

void ADC_init(ADC_Config_t* ADC_Config)
{
	Global_ADC_Config = *ADC_Config;
	
	/*-----------------------------*/
	/*1) Set ADC Mode (ADCSRA >> ADSC)*/
	//-----------------------------
	ADCSRA |= ADC_Config->ADC_MODE;
	
	/*-----------------------------*/
	/*2) Set ADC Vref (ADMUX >> REFS0)*/
	/*-----------------------------*/
	ADMUX |= ADC_Config->ADC_VREF;
	
	/*-----------------------------*/
	/*3) Set Result Presentation (ADMUX >> ADLAR)*/
	/*-----------------------------*/
	ADMUX |= ADC_Config->ADC_Result_Presentation;
	
	/*-----------------------------*/
	/*4) Set ADC Prescaler (ADCSRA >> ADPS0:1)*/
	/*-----------------------------*/
	ADCSRA |= ADC_Config->ADC_PRESCALER;
	
	/*-----------------------------*/
	/*5) Enable/Disable IRQ (ADCSRA >> ADIE)*/
	/*-----------------------------*/
	ADCSRA |= ADC_Config->IRQ_Enable;
	
	
	if (ADC_Config->IRQ_Enable == ADC_IRQ_ENABLE)
	{
		sei();
	}
	else{}

	/*-----------------------------*/
	/*6) Enable ADC Module        */
	/*-----------------------------*/
	SET_BIT(ADCSRA, 7);
	
	/*-----------------------------*/
	/*6) Start Conversion with ADC FREE Running mode*/
	/*-----------------------------*/
	if(ADC_Config->ADC_MODE == ADC_MODE_FREE_RUNNING){
		SET_BIT(ADCSRA, 6);
	}
	else{}
}


void ADC_ReadData(Channel_Select_t channel, uint16* data, Polling_Mechanism_t Polling){
	
	/*-----------------------------*/
	/*1) Reset ADMUX*/
	ADMUX &= ~(0x1F);
	
	/*-----------------------------
	/*2) select ADC Channel and Configure it to be Input*/
	/*-----------------------------*/
	ADMUX |= (uint8_t)channel;
	CLEAR_BIT(DDRA, channel);
	
	/*-----------------------------*/
	/*3) Start Conversion          */
	/*-----------------------------*/
	if(Global_ADC_Config.ADC_MODE == ADC_MODE_SINGLE_CONVERSION){
		SET_BIT(ADCSRA, 6);
	}
	else{}
	/*-----------------------------*/
	/*4) Check for using Polling Mechanism*/
	/*-----------------------------*/
	if(Polling == Polling_ENABLE){
		while(GET_BIT(ADCSRA, 4)==0)
		{}
	}
	else{}
	
	/*-----------------------------*/
	/*5) Read Converted Data       */
	/*-----------------------------*/
	if(Global_ADC_Config.ADC_Result_Presentation == ADC_Result_Presentation_RIGHT){
		*data = (ADCL | ((ADCH & (0x03)) << 8));
	}
	else{
		*data = ((ADCL & (0xC0)) >> 6) | (ADCH << 2);
	}
	
	/*-----------------------------*/
	/*6) Clear ADIF flag           */
	/*-----------------------------*/
	CLEAR_BIT(ADCSRA, 4);
}

ISR(ADC_vect){
	Global_ADC_Config.P_CallBack();
}


