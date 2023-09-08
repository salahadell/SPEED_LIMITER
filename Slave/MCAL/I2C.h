/*
 * I2C.h
 *
 * Created: 9/5/2023 4:40:13 PM
 *  Author: salah
 */ 


#ifndef I2C_H_
#define I2C_H_
#define F_CPU 16000000UL
#include "std_types.h"
//#include "BitMap.h"
/*******************************************************************************
 *                                I2C registers                                 *
 *******************************************************************************/

#define TWBR *((volatile uint8*)(0x20))
#define TWCR *((volatile uint8*)(0x56))
#define TWSR *((volatile uint8*)(0x21))
#define TWDR *((volatile uint8*)(0x23))
#define TWAR *((volatile uint8*)(0x22))
/*******************************************************************************
 *                                IMP BITS and MACROS and ENUM                 *
 *******************************************************************************/
#define TWINT 7 
#define TWEA  6
#define TWSTA 5
#define TWSTO 4
#define TWWC  3
#define TWEN  2
#define TWIE  0

#define I2C_STANDARD_SPEED_400K 400000
#define WITH_ACK 1
#define WITH_NACK 0

//ENABLE GENERAL CALL BIT
#define TWGCE 0

//prescaler value TWPS1 TWPS0
typedef enum{Prescaler_1,Prescaler_4,Prescaler_16,Prescaler_64}Prescaler;
	
//GENERAL CALL MODE
#define GCALL_ENABLE  1
#define GCALL_DISABLE 0


//ACK MACROS
typedef enum{NACK_RECEIVED,ACK_RECEIVED,ERROR}STATUS;
	
/*******************************************************************************
 *                                Status register conditions                    *
 *******************************************************************************/

#define START_ACK                0x08 /* start has been sent */
#define REP_START_ACK            0x10 /* repeated start */

//MASTER
#define SLAVE_ADD_AND_WR_ACK     0x18 /* Master transmit ( slave address + Write request ) ACK */
#define SLAVE_ADD_AND_WR_NACK    0x20 /* Master transmit ( slave address + Write request ) NACK */
#define SLAVE_ADD_AND_RD_ACK     0x40 /* Master transmit ( slave address + Read request ) ACK */
#define SLAVE_ADD_AND_RD_NACK    0x48 /* Master transmit ( slave address + Read request ) NACK */
#define MSTR_WR_BYTE_ACK         0x28 /* Master transmit data and received ACK */
#define MSTR_WR_BYTE_NACK        0x30 /* Master transmit data and received NACK */
#define MSTR_RD_BYTE_WITH_ACK    0x50 /* Master received data and send ACK to slave */
#define MSTR_RD_BYTE_WITH_NACK   0x58 /* Master received data and send not ACK to slave */

//SLAVE
#define SLAVE_ADD_RCVD_RD_REQ        0xA8 /* means that slave address is received with read request */
#define SLAVE_ADD_RCVD_WR_REQ        0x60 /* means that slave address is received with write request and ACK returned */
#define SLAVE_BYTE_TRANSMITTED_ACK   0xB8 /* means that the written byte is transmitted and ACK received */
#define SLAVE_BYTE_TRANSMITTED_NACK  0xC0 /* means that the written byte is transmitted and NACK received */
#define SLAVE_DATA_RECEIVED_ACK      0x80 /* means that a byte is received and ACK returned */
#define SLAVE_DATA_RECEIVED_NACK     0x88 /* means that a byte is received and NACK returned */

/*******************************************************************************
 *                                FUNCTIONS API                    *
 *******************************************************************************/

void I2C_start();
void I2C_restart();
void I2C_stop();
uint8 Master_read(uint8 ack);
uint8 Slave_read(uint8 ack);
STATUS Master_write(uint8 data);
STATUS Slave_write(uint8 data);
void master_init(uint32 SCL_FREQ,uint8 prescaler);
STATUS master_transmit_write(uint8 Slave_ADD);
STATUS master_transmit_read(uint8 Slave_ADD);
void slave_init(uint8 address,uint8 GCALL_MODE);
STATUS Data_Acknowledge_received_from_master();
STATUS Data_Acknowledge_received_from_slave();
STATUS ADDRESS_Acknowledge_received_from_slave();
uint8 READ_BIT(uint8 REG,uint8 BIT);

#endif /* I2C_H_ */