
/*
 * AES_interface.h
 *
 * Created: 5/29/2024 10:50:10 AM
 *  Author: NotFound
 */ 

#ifndef AES_INTERFACE_H
#define AES_INTERFACE_H

#include <stdint.h>

#define AES_BLOCK_SIZE 16

void AES_init(const uint8_t *key);
void AES_encrypt(const uint8_t *input, uint8_t *output);

#endif // AES_INTERFACE_H
