 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the SPI AVR driver
 *
 * Author: shawky
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
/*******************************************************************************
 *                                SPI registers                                 *
 *******************************************************************************/
#define SPCR  *((volatile uint8*) 0x2D)
#define SPSR  *((volatile uint8*) 0x2E)
#define SPDR  *((volatile uint8*) 0x2F)
/*******************************************************************************
 *                                SPCR BITS                                 *
 *******************************************************************************/
#define SPCR_SPIE  7
#define SPCR_SPE   6
#define SPCR_DORD  5
#define SPCR_MSTR  4
#define SPCR_CPOL  3
#define SPCR_CPHA  2
#define SPCR_PRE   0
/*******************************************************************************
 *                                SPSR BITS                                 *
 *******************************************************************************/
#define SPSR_SPIF  7
#define SPSR_WCOL  6
#define SPSR_SPI2X  0

#define SPIE_EN  1
#define SPIE_DS  0

#define SPE_EN   1
#define SPE_DS   0

#define DORD_LSB_FIRST  1
#define DORD_MSB_FIRST  0

#define MSTR_MASTER_MODE  1
#define MSTR_SLAVE_MODE   0

#define CPOL_RISING    0
#define CPOL_FALLING   1    

#define CPHA_SAMPLE  0
#define CHPA_SETUP   1

#define SPI_PRE4     0
#define SPI_PRE16    1
#define SPI_PRE64    2
#define SPI_PRE128   3

#define SPI2X_EN   1
#define SPI2X_DS   0
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 0xFF

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the SPI device as Master.
 */
void SPI_initMaster(void); 

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);

#endif
