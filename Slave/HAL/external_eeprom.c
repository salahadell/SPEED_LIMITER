 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Salah
 *
 *******************************************************************************/
#include "external_eeprom.h"
#include "I2C.h"
STATUS status;

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    I2C_start();
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    status= master_transmit_write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (status ==ERROR)
        return NOTSUCCESS; 
		 
    /* Send the required memory location address */
    status=Master_write((uint8)(u16addr));
    if (status ==ERROR)
        return NOTSUCCESS;
		
    /* write byte to eeprom */
    status=Master_write(u8data);
    if (status ==ERROR)
        return NOTSUCCESS;

    /* Send the Stop Bit */
    I2C_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    I2C_start();
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    status=master_transmit_write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (status ==ERROR)
        return NOTSUCCESS; 
         
    /* Send the required memory location address */
    status=Master_write((uint8)(u16addr));
    if (status ==ERROR)
        return NOTSUCCESS;
		
    /* Send the Repeated Start Bit */
    I2C_restart();
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    status=master_transmit_read((uint8)((0xA0) | ((u16addr & 0x0700)>>7)|1));
    if (status ==ERROR)
        return NOTSUCCESS;

    /* Read Byte from Memory without send ACK */
    *u8data = Master_read(WITH_NACK);

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}
