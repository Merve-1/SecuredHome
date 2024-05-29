
/*
 * EEPROM_interface.h
 *
 * Created: 5/28/2024 11:19:19 AM
 *  Author: NotFound
 */ 



#ifndef EEPROM_INTERFACE_H_
#define  EEPROM_INTERFACE_H_

//APIs Prototypes

void EEPROM_voidInit			(void);
void EEPROM_voidWriteByte		(u16 copy_u16WordAddress, u8 copy_u8Data);
void EEPROM_voidReadByte		(u16 copy_u16WordAddress, u8* copy_pu8Data);

#endif   /*EEPROM_INTERFACE_H_*/