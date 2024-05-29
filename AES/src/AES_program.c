
/*
 * AES_program.c
 *
 * Created: 5/29/2024 10:49:47 AM
 *  Author: NotFound
 */ 


#include "AES_interface.h"
#include <string.h>

// AES S-box (subset shown for brevity)
static const uint8_t sbox[256] = {
	// Full S-box array values here...
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	// ... more values ...
};

// AES round keys (dummy implementation)
static uint8_t round_keys[AES_BLOCK_SIZE * 11];

static void KeyExpansion(const uint8_t *key) {
	// Dummy key expansion logic here
	// For simplicity, we will just copy the key to the first round key
	memcpy(round_keys, key, AES_BLOCK_SIZE);
}

void AES_init(const uint8_t *key) {
	KeyExpansion(key);
}

static void SubBytes(uint8_t *state) {
	// SubBytes transformation using the S-box
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
		state[i] = sbox[state[i]];
	}
}

static void ShiftRows(uint8_t *state) {
	// ShiftRows transformation
	uint8_t temp;

	// Row 1 shift left by 1
	temp = state[1];
	state[1] = state[5];
	state[5] = state[9];
	state[9] = state[13];
	state[13] = temp;

	// Row 2 shift left by 2
	temp = state[2];
	state[2] = state[10];
	state[10] = temp;
	temp = state[6];
	state[6] = state[14];
	state[14] = temp;

	// Row 3 shift left by 3
	temp = state[3];
	state[3] = state[15];
	state[15] = state[11];
	state[11] = state[7];
	state[7] = temp;
}

static void MixColumns(uint8_t *state) {
	// MixColumns transformation (dummy implementation)
	// Full implementation requires Galois field multiplication
	// Here is a simple placeholder that doesn't do actual MixColumns
	for (int i = 0; i < 4; ++i) {
		uint8_t a = state[i * 4 + 0];
		uint8_t b = state[i * 4 + 1];
		uint8_t c = state[i * 4 + 2];
		uint8_t d = state[i * 4 + 3];
		state[i * 4 + 0] = a ^ b ^ c ^ d;
		state[i * 4 + 1] = a ^ b ^ c ^ d;
		state[i * 4 + 2] = a ^ b ^ c ^ d;
		state[i * 4 + 3] = a ^ b ^ c ^ d;
	}
}

static void AddRoundKey(uint8_t *state, const uint8_t *round_key) {
	// AddRoundKey transformation
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
		state[i] ^= round_key[i];
	}
}

void AES_encrypt(const uint8_t *input, uint8_t *output) {
	uint8_t state[AES_BLOCK_SIZE];
	memcpy(state, input, AES_BLOCK_SIZE);

	AddRoundKey(state, round_keys);

	for (int round = 1; round < 10; ++round) {
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, round_keys + round * AES_BLOCK_SIZE);
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, round_keys + 10 * AES_BLOCK_SIZE);

	memcpy(output, state, AES_BLOCK_SIZE);
}
