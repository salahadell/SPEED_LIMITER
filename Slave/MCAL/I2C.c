/*
 * I2C.c
 *
 * Created: 9/5/2023 4:40:30 PM
 *  Author: salah
 */ 
#include "I2C.h"

void I2C_start(void)
{
	TWCR=(1<<TWINT|1<<TWSTA|1<<TWEN);
	/*making sure that the int flag is set to one*/
	while(READ_BIT(TWCR,TWINT)==0){}
	/*read the status register to make sure that the start ACK received*/
	while((TWSR&0xF8)!=START_ACK){}
}
void I2C_restart(void)
{
	TWCR=(1<<TWINT|1<<TWSTA|1<<TWEN);
	/*making sure that the int flag is set to one*/
	while(READ_BIT(TWCR,TWINT)==0){}
	/*read the status register to make sure that the start ACK received*/
	while((TWSR&0xF8)!=REP_START_ACK){}
}
void I2C_stop(void)
{
	TWCR=(1<<TWINT|1<<TWSTO|1<<TWEN);
	
}
uint8 Slave_read(uint8 ack)
{
	if(ack==1)
	{
		/*send ACK*/
		TWCR=(1<<TWINT|1<<TWEA|1<<TWEN);
		while(READ_BIT(TWCR,TWINT)==0){}
		while((TWSR&0xF8)!=SLAVE_DATA_RECEIVED_ACK){}
	}
	else
	{
		/*send NACK*/
		TWCR=(1<<TWINT|1<<TWEN);
		while(READ_BIT(TWCR,TWINT)==0){}
		while((TWSR&0xF8)!=SLAVE_DATA_RECEIVED_NACK){}
	}
	return TWDR;
}
STATUS Slave_write(uint8 data)
{
		TWDR=data;	
		/*send data*/
		TWCR=(1<<TWINT|1<<TWEN);
		while(READ_BIT(TWCR,TWINT)==0){}
		/*return status of TWSR (ACK,NACK,ERROR)*/
		return Data_Acknowledge_received_from_master();
}
uint8 Master_read(uint8 ack)
{
	if(ack==1)
	{
		/*send ACK*/
	  TWCR=(1<<TWINT|1<<TWEA|1<<TWEN);
	  while(READ_BIT(TWCR,TWINT)==0){}
	  while((TWSR&0xF8)!=MSTR_RD_BYTE_WITH_ACK){}
	}
	else
	{
		/*send NACK*/
	 TWCR=(1<<TWINT|1<<TWEN);
	 while(READ_BIT(TWCR,TWINT)==0){}
	 while((TWSR&0xF8)!=MSTR_RD_BYTE_WITH_NACK){}
	}
	
	return TWDR;
}
STATUS Master_write(uint8 data)
{
	TWDR=data;
	/*send data*/
	TWCR=(1<<TWINT|1<<TWEN);
	/*making sure that the int flag is set to one*/
	while(READ_BIT(TWCR,TWINT)==0){}
	/*return status of TWSR (ACK,NACK,ERROR)*/
	return Data_Acknowledge_received_from_slave();
	
}
void master_init(uint32 SCL_FREQ,Prescaler prescaler)
{
	TWSR|=prescaler;
	switch(prescaler)
	{
		case 0:
			TWBR=(uint8)(((F_CPU/SCL_FREQ)-16)/(2));
			break;
		case 1:
			TWBR=(uint8)(((F_CPU/SCL_FREQ)-16)/(2*4));
			break;
		case 2:
			TWBR=(uint8)(((F_CPU/SCL_FREQ)-16)/(2*16));
			break;
		case 3:
			TWBR=(uint8)(((F_CPU/SCL_FREQ)-16)/(2*64));
			break;
		default:
		    break;
	}
}
STATUS master_transmit_write(uint8 Slave_ADD)
{
	/*set the most seven bits to the slave address and first bit to 0*/
	TWDR=Slave_ADD;
	/*send data*/
	TWCR=(1<<TWINT|1<<TWEN);
	/*making sure that the int flag is set to one*/
	while(READ_BIT(TWCR,TWINT)==0){}
	/*return status of TWSR (ACK,NACK,ERROR)*/
	return ADDRESS_Acknowledge_received_from_slave();
}
STATUS master_transmit_read(uint8 Slave_ADD)
{
	/*set the most seven bits to the slave address and first bit to 1*/
	TWDR=Slave_ADD;
	/*send data*/
	TWCR=(1<<TWINT|1<<TWEN);
	/*making sure that the int flag is set to one*/
	while(READ_BIT(TWCR,TWINT)==0){}
	/*return status of TWSR (ACK,NACK,ERROR)*/
	return ADDRESS_Acknowledge_received_from_slave();
}
void slave_init(uint8 address,uint8 GCALL_MODE)
{
	/*set slave address and GENERAL CALL*/
	TWAR=(address<<1|GCALL_MODE);
}
STATUS ADDRESS_Acknowledge_received_from_slave(void)
{
	STATUS status;
		if((TWSR&0xF8)==SLAVE_ADD_AND_WR_ACK||(TWSR&0xF8)==SLAVE_ADD_AND_RD_ACK)
		{
			status=ACK_RECEIVED;
		}
		else if((TWSR&0xF8)==SLAVE_ADD_AND_WR_NACK||(TWSR&0xF8)==SLAVE_ADD_AND_RD_NACK)
		{
			status=NACK_RECEIVED;
		}
		else
		{
			status=ERROR;

		}
		return status;
}
STATUS Data_Acknowledge_received_from_slave(void)
{
		STATUS status;
		if((TWSR&0xF8)==MSTR_WR_BYTE_ACK)
		{
			status=ACK_RECEIVED;
		}
		else if((TWSR&0xF8)==MSTR_WR_BYTE_NACK)
		{
			status=NACK_RECEIVED;
		}
		else
		{
			status=ERROR;

		}
		return status;
}
STATUS Data_Acknowledge_received_from_master(void)
{
	STATUS status;
	if((TWSR&0xF8)==SLAVE_BYTE_TRANSMITTED_ACK)
	{
		status=ACK_RECEIVED;
	}
	else if((TWSR&0xF8)==SLAVE_BYTE_TRANSMITTED_NACK)
	{
		status=NACK_RECEIVED;
	}
	else
	{
		status=ERROR;

	}
	return status;
}
uint8 READ_BIT(uint8 REG,uint8 BIT)
{
	return ((REG>>BIT)&1);
}