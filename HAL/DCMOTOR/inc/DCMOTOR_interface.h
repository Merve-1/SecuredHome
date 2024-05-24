
/*
 * DCMOTOR_interface.h
 *
 * Created: 5/24/2024 12:09:34 PM
 *  Author: NotFound
 */ 

#ifdef DCMOTOR_INTERFACE_H_
#endif DCMOTOR_INTERFACE_H_

#define DCMOTOR_A		1

#define DCMOTOR_CLOCK_WISE		1
#define DCMOTOR_COUNTER_CLOCK_WISE	2

void DCMOTOR_voidInit			(u8 copy_u8MotorId);
void DCMOTOR_voidOn				(u8 copy_u8MotorId, u8 copy_u8MotorDirection);
void DCMOTOR_voidControlSpeed   (u8 copy_u8MotorId, u8 copy_u8MotorDirection, u8 copy_u8Speed);
void DCMOTOR_voidOff			(u8 copy_u8MotorId);

#endif /* DCMOTOR_INTERFACE_H_ */