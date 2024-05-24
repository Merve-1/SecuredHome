
/*
 * EXTI_program.c
 *
 * Created: 5/10/2024 5:24:47 PM
 *  Author: NotFound
 */ 

/* UTILES LIG */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "EXTI_register.h"
#include "EXTI_register.h"

void EXTI_voidEnable(u8 copy_u8InterruptSource, u8 copy_u8TriggerEdge);
void EXTI_VoidDisable(u8 copy_u8InterruptSource);