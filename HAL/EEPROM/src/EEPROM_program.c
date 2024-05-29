
/*
 * EEPROM_program.c
 *
 * Created: 5/28/2024 11:20:06 AM
 *  Author: NotFound
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>


/* UTILES LEB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL  */
#include "TWI_interface.h"

/* HAL   */
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_voidInit(void) {
	TWI_voidInitMaster();
}

void EEPROM_voidWriteByte(u16 copy_u16WordAddress, u8 copy_u8Data){
	u8 local_u8DeviceAddress = (copy_u16WordAddress>>8) | EEPROM_FIXED_ADDRESS;
	
	//send start condition
	TWI_voidSendStartCondition();
	
	//send device address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
	
	//send word address 
	TWI_voidTransmitMasterDataByte((u8)copy_u16WordAddress);
	
	//send byte data
	TWI_voidTransmitMasterDataByte(copy_u8Data);
	
	//send stop condition
	TWI_voidSendStopCondition();
	
	//self-timed write cycle delay
	_delay_ms(5);
}

void EEPROM_voidReadByte(u16 copy_u16WordAddress, u8* copy_pu8Data){
	if(copy_pu8Data != NULL){
		u8 local_u8DeviceAddress = (copy_u16WordAddress>>8) | EEPROM_FIXED_ADDRESS;
		
		//send start condition
		TWI_voidSendStartCondition();
		
		//send device address with write operation 
		TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
		
		//send word address
		TWI_voidTransmitMasterDataByte((u8)copy_u16WordAddress);
		
		//send repeated start condition in order to switch i2c operation
		TWI_voidSendRepeatedStartCondition();
		
		//send slave address with read operation
		TWI_voidSendSlaveAddWithWrite(local_u8DeviceAddress);
		
		//read byte data and respond without ACK
		TWI_voidReceiveMasterDataByteWithNack(copy_pu8Data);
		
		//send stop condition
		TWI_voidSendStopCondition();
		
		//self-timed write cycle delay
		_delay_ms(5);
		

		
	}
	else{
		//return error state
	}
	
}