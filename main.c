/*		Documentation								*
 *		Software component : STD_TYPES.h			*
 *		Created: 4/8/2024 7:48:21 PM				*
 *		Author: NotFound							*
 *		Version : 1.0								* 
 *		VersionDescription: no description yet		*
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

// UTILES_LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "MCAL/DIO/inc/DIO_interface.h"
#include "HAL/LED/inc/LED_interface.h"
#include "HAL/SWITCH/inc/SWITCH_interface.h"
#include "HAL/BUZZER/inc/BUZZER_interface.h"
#include "HAL/LCD/inc/LCD_interface.h"
#include "HAL/KEYPAD/inc/KPD_interface.h"
#define PASSWORD_LENGTH 4 // Assuming the password length is 4 digits
#define MAX_TRIALS      3   // Maximum number of password entry trials


int main(void)
{
	char password[PASSWORD_LENGTH + 1];        // Array to store the password (+1 for null terminator)
	char input_password[PASSWORD_LENGTH + 1];  // Array to store the user input password
	int i, trials, trailNumber = 0;
	BOOL password_set = false;

	LCD_voidInit(); // Initialize LCD
	KPD_voidInit(); // Initialize Keypad

	// Ask the user to set the password
	LCD_voidSendCommand(0x01); // Clear Display
	LCD_voidDisplayString("Set password:");

	// Getting the password from the user
	for (i = 0; i < PASSWORD_LENGTH; ++i) {
		char key;
		do {
			KPD_voidGetValue(&key);
		} while (key == KPD_NOT_PRESSED); // Wait until a key is pressed
		password[i] = key;
		LCD_voidDisplayChar('*'); // Display '*' instead of actual digits
	}
	password[PASSWORD_LENGTH] = '\0'; // Null terminate the password
	password_set = true;

	while (1) {
		// Clear display
		LCD_voidSendCommand(0x01); // Clear Display

		if (password_set) {
			// Ask the user to enter the password to unlock the door
			LCD_voidDisplayString("Enter password:");

			// Getting the password from the user
			for (i = 0; i < PASSWORD_LENGTH; ++i) {
				char key;
				do {
					KPD_voidGetValue(&key);
				} while (key == KPD_NOT_PRESSED); // Wait until a key is pressed

				input_password[i] = key;
				LCD_voidDisplayChar('*'); // Display '*' instead of actual digits
			}
			input_password[PASSWORD_LENGTH] = '\0'; // Null terminate the input password

			// Check if the input password matches the stored password
			if (strcmp(password, input_password) == 0) {
				// Correct password entered, display "Door opened!" and exit the loop
				LCD_voidSendCommand(0x01); // Clear Display
				LCD_voidDisplayString("Door opened!");
				break;
				} else {
				// Incorrect password entered
				trials++;

				if (trials >= MAX_TRIALS) {
					// Maximum trials reached, display "Locked!" and exit the loop
					LCD_voidSendCommand(0x01); // Clear Display
					LCD_voidDisplayString("Locked!");
					break;
					} else {
					// Display "One trial passed" and wait for a while before clearing the display
					LCD_voidSendCommand(0x01); // Clear Display
					trailNumber++;
					if (1 == trailNumber){
					LCD_voidDisplayString("One trial passed");
					_delay_ms(2000); // Delay to read the message
					}
					else if (2 == trailNumber){
						LCD_voidDisplayString("Second trial passed");
						_delay_ms(2000); // Delay to read the message
					}
					
					// Ask the user to re-enter the password
					continue;
				}
			}
			} else {
			// Inform the user to set the password first
			LCD_voidDisplayString("Set password first");
			break; // Exit the loop as the password needs to be set first
		}
	}
	

	
	while(1); // Infinite loop
	
	return 0;
	
	/************************************************************************/
	/*                          Using LCD & KPD Drivers                     */
	/************************************************************************/
	/*
	u8 local_u8Key;
	KPD_voidInit();
	LCD_voidInit();
	
	while(1){
		
		KPD_voidGetValue(&local_u8Key);
		if(local_u8Key != KPD_NOT_PRESSED)
		{
			LCD_voidDisplayChar(local_u8Key);
		}
		
	}
	
		
	*/
	/*
	LCD_voidInit();
	LCD_voidDisplayChar('D');
	LCD_voidDisplayChar('5');
	LCD_voidDisplayChar('9');
	//LCD_voidDisplayString((u8*) "Embedded");// casting string (pointer to character)
	

	// Wait for a short duration
	_delay_ms(1000);

	// Clear the LCD
	LCD_voidClear();
	_delay_ms(1000);
	
	*/


	
	
	/************************************************************************/
	/*                       Using Switch Drivers                           */
	/************************************************************************/
	/*
	// Initialize switches
   
	DIO_voidSetPinDirection(SWITCH_0_PORT,SWITCH_0_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(SWITCH_1_PORT,SWITCH_1_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(SWITCH_2_PORT,SWITCH_2_PIN, DIO_PIN_INPUT);

    // Initialize LEDs
    DIO_voidSetPinDirection(LED_0_PORT, LED_0_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LED_1_PORT, LED_1_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LED_2_PORT, LED_2_PIN, DIO_PIN_OUTPUT);
	
	// Initialize Buzzer
	DIO_voidSetPinDirection(BUZZER_PORT,BUZZER_PIN, DIO_PIN_OUTPUT);

    
    u8 local_u8Sw0State, local_u8Sw1State, local_u8Sw2State;
    
    while (1) {
        // Get state of switches
        local_u8Sw0State = SWITCH_u8GetState(SWITCH_0_PORT, SWITCH_0_PIN);
        local_u8Sw1State = SWITCH_u8GetState(SWITCH_1_PORT, SWITCH_1_PIN);
        local_u8Sw2State = SWITCH_u8GetState(SWITCH_2_PORT, SWITCH_2_PIN);
        
        // Control LEDs based on switch states
        if (local_u8Sw0State) {
            DIO_voidSetPinValue(LED_0_PORT, LED_0_PIN, DIO_PIN_HIGH);
        } else {
            DIO_voidSetPinValue(LED_0_PORT, LED_0_PIN, DIO_PIN_LOW);
        }
        
        if (local_u8Sw1State) {
            DIO_voidTogglePinValue(LED_1_PORT, LED_1_PIN);
            //DIO_voidTogglePinValue(DIO_PORTA, DIO_PIN3);
			DIO_voidTogglePinValue(BUZZER_PORT,BUZZER_PIN);

        }
        
        if (local_u8Sw2State) {
            DIO_voidSetPinValue(LED_2_PORT, LED_2_PIN, DIO_PIN_LOW);
        } else {
            DIO_voidSetPinValue(LED_2_PORT, LED_2_PIN, DIO_PIN_HIGH);
        }
    }
	*/
	/************************************************************************/
	/*				Task: 1) Turn on led0 if sw0 is pressed else off        */
	/*				2) led2 on if sw2 isn't pressed else off                */
	/*				3) toggle led1, buzzer if sw1 is pressed                */
	/************************************************************************/
	/*
	u8 local_u8Sw0State, local_u8Sw1State, local_u8Sw2State;
	
	// DIO initalization 
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT); // LED0
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT); // LED1
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT); // LED2
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT); // BUZZ
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_PIN_INPUT);  // SW0
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_PIN_INPUT);  // SW1
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);  // SW2
	
	
	while (1){
		DIO_voidGetPinValue(DIO_PORTB,DIO_PIN0,&local_u8Sw0State); 
		DIO_voidGetPinValue(DIO_PORTD,DIO_PIN6,&local_u8Sw1State); 
		DIO_voidGetPinValue(DIO_PORTD,DIO_PIN2,&local_u8Sw2State); 
		
		if(1 == local_u8Sw0State){
				DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);//LED0
		}else{
				DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);//LED0
		}
		if(1 == local_u8Sw1State){
				DIO_voidTogglePinValue(DIO_PORTC,DIO_PIN7); //LED1 TOG
				DIO_voidTogglePinValue(DIO_PORTA,DIO_PIN3); //BUZZ TOG
		}
		if (1 == local_u8Sw2State){
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_LOW);//LED2
			
		}else{
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);//LED2
		}
		
		
	}
	
	
	*/
	/*************************************************************************************/
	/* TASK: using DIO module turn on led0 and led2, then toggle led1, buzzer every 0.5s */
	/*************************************************************************************/
	// DIO INITIALIZATION
	/*DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT); // LED0
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_OUTPUT); // LED1
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_OUTPUT); // LED2
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT); // BUZZ
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);//LED0
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);//LED2
	
    while (1) 
    {
		DIO_voidTogglePinValue(DIO_PORTC,DIO_PIN7); //LED1 TOG
		DIO_voidTogglePinValue(DIO_PORTA,DIO_PIN3); //BUZZ TOG
		_delay_ms(500);
    }*/

/* Driver code
	// Initialize the LED
    LED_voidInit();

    while (1) {
        // Turn on the LED
        LED_voidTurnOn();
		_delay_ms(500);
        
        // Turn off the LED
        LED_voidTurnOff();
		_delay_ms(500);


        // Toggle the LED state
        LED_voidToggle();
		_delay_ms(500);

    }

    return 0;
*/
}

