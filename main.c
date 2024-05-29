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
#include "HAL/DC/inc/DCMOTOR_interface.h"
#include "HAL/Servo/inc/SRVM_interface.h"
#include "HAL/EEPROM/inc/EEPROM_interface.h"
#include "AES/inc/AES_interface.h" 


#define PASSWORD_LENGTH 4 // Assuming the password length is 4 digits
#define MAX_TRIALS      3   // Maximum number of password entry trials
#define AES_BLOCK_SIZE  16  // AES block size


void encryptPassword(const char *password, uint8_t *encrypted_password, const uint8_t *aes_key) {
	// Ensure the password is AES_BLOCK_SIZE long
	uint8_t buffer[AES_BLOCK_SIZE] = {0};
	strncpy((char *)buffer, password, PASSWORD_LENGTH);
	AES_encrypt(buffer, encrypted_password);
}

int main(void) {
	char password[PASSWORD_LENGTH + 1]; // Array to store the password (+1 for null terminator)
	char input_password[PASSWORD_LENGTH + 1]; // Array to store the user input password
	uint8_t encrypted_password[AES_BLOCK_SIZE]; // Array to store the encrypted password
	const uint8_t aes_key[AES_BLOCK_SIZE] = "1234567890ABCDEF"; // Example AES key (16 bytes)
	int i, trials = 0, trailNumber = 0;
	BOOL password_set = false;

	// Initialize peripherals
	LCD_voidInit(); // Initialize LCD
	KPD_voidInit(); // Initialize Keypad
	DCMOTOR_voidInit(DCMOTOR_A); // Initialize DC motor
	SRVM_voidInit(); // Initialize Servo motor
	LED_voidInit(DIO_PORTD, DIO_PIN7); // Initialize LED
	// Initialize AES with the key
	AES_init(aes_key);

	// Check if the initializations are successful
	LCD_voidSendCommand(0x01); // Clear Display
	LCD_voidDisplayString("Init Done");
	_delay_ms(2000);

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
	encryptPassword(password, encrypted_password, aes_key); // Encrypt the password
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

			// Encrypt the input password
			uint8_t encrypted_input_password[AES_BLOCK_SIZE] = {0};
			encryptPassword(input_password, encrypted_input_password, aes_key);

			// Check if the encrypted input password matches the stored encrypted password
			if (memcmp(encrypted_password, encrypted_input_password, AES_BLOCK_SIZE) == 0) {
				// Correct password entered, display "Door opened!" and exit the loop
				LCD_voidSendCommand(0x01); // Clear Display
				LCD_voidDisplayString("Door opened!");

				// Turn on the LED
				LED_voidTurnOn(DIO_PORTD, DIO_PIN7);
				_delay_ms(5000);

				// Turn off the LED
				LED_voidTurnOff(DIO_PORTD, DIO_PIN7);

				// Turn on the motor
				DCMOTOR_voidOn(DCMOTOR_A, DCMOTOR_CLOCK_WISE);
				_delay_ms(5000); // Keep the motor running for 5 seconds

				// Turn off the motor
				DCMOTOR_voidOff(DCMOTOR_A);

				// Turn the servo motor to open the door
				SRVM_voidOn(90); // Adjust the angle as needed to represent door opening
				_delay_ms(5000); // Keep the servo in the open position for 5 seconds
				SRVM_voidOff();

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
					// Display trial number passed and wait for a while before clearing the display
					LCD_voidSendCommand(0x01); // Clear Display
					trailNumber++;
					if (trailNumber == 1) {
						LCD_voidDisplayString("One trial passed");
						} else if (trailNumber == 2) {
						LCD_voidDisplayString("Second trial passed");
					}
					_delay_ms(2000); // Delay to read the message

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

	while (1); // Infinite loop

	return 0;
}