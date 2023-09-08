 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Source file for the SPI AVR driver
 *
 * Author: Shawky
 *
 *******************************************************************************/
#include "util/delay.h"
#include "spi.h"
#include "GPIO.h" /* To Setup the SPI pins direction */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void) 
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output 
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	DIO_SetPinDir(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN6,DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);
	
    /************************** SPCR Description **************************
     * SPIE    = 0 Disable SPI Interrupt
     * SPCR_SPE     = 1 Enable SPI Driver
     * DORD    = 0 Transmit the MSB first
     * SPCR_MSTR    = 1 Enable Master
     * CPOL    = 0 SCK is low when idle
     * CPHA    = 0 Sample Data with the raising edge
     * SPR1:0  = 00 Choose SPI clock = Fosc/4
     ***********************************************************************/
	SPCR = (1<<SPCR_SPE) | (1<<SPCR_MSTR);

	/* Clear the SPSR_SPIF bit in SPSR to Choose SPI clock = Fosc/4 */
	SPSR &= ~(1<<SPSR_SPIF);
}

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void)
{ 
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DIO_SetPinDir(DIO_PORTB,DIO_PIN5,DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN7,DIO_PIN_INPUT);

	/************************** SPCR Description **************************
	 * SPIE    = 0 Disable SPI Interrupt
	 * SPCR_SPE     = 1 Enable SPI Driver
	 * DORD    = 0 Transmit the MSB first
	 * SPCR_MSTR    = 0 Disable Master
	 * CPOL    = 0 SCK is low when idle
	 * CPHA    = 0 Sample Data with the raising edge
	 * SPR1:0  = 00 Choose SPI clock = Fosc/4
	 ***********************************************************************/
	SPCR = (1<<SPCR_SPE);

	/* Clear the SPSR_SPIF bit in SPSR to Choose SPI clock = Fosc/4 */
	SPSR &= ~(1<<SPSR_SPIF);
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPDR = data;

	/* Wait until SPI interrupt flag SPIF = 1 (data has been sent/received correctly) */
	while(BIT_IS_CLEAR(SPSR,SPSR_SPIF)){}
	_delay_ms(100);
	/*
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;
	uint8 received_data = 0;

	/* Send the whole string */
	while(str[i] != '\0')
	{
		/*
		 * received_data contains the received data from the other device.
		 * It is a dummy data variable as we just need to send the string to other device.
		 */
		received_data = SPI_sendReceiveByte(str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
