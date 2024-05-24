
/*
 * DCMOTOR_program.c
 *
 * Created: 5/24/2024 12:09:51 PM
 *  Author: NotFound
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "PWM_interface.h"

/* HAL */
#include "DCMOTOR_interface.h"
#include "DCMOTOR_config.h"


void DCMOTOR_voidInit			(u8 copy_u8MotorId);
void DCMOTOR_voidOn				(u8 copy_u8MotorId, u8 copy_u8MotorDirection);
void DCMOTOR_voidControlSpeed   (u8 copy_u8MotorId, u8 copy_u8MotorDirection, u8 copy_u8Speed);
void DCMOTOR_voidOff			(u8 copy_u8MotorId);


