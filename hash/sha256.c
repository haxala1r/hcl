#include "../include/hash.h"
#include "../include/common.h"
#include <stdlib.h>
#include <string.h>

/* This can be computed in run-time, but I decided it would be better to simply
 * hard-code them.
 */
uint32_t round_constants[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


/* DO NOT USE THIS DIRECTLY UNLESS YOU HAVE A GOOD REASON TO.
 * see include/hash.h line 9 for an explanation.
 */
void HCL_sha256_unsafe(unsigned char *msg, uint64_t msg_len, char *out) {
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	/* The padding (unsafe part) */
	uint64_t new_len = msg_len;
	msg[new_len++] = 0x80;

	uint64_t bits = new_len * 8 % 512;
	while (bits != 448) {
		msg[new_len++] = 0;

		bits = (new_len * 8) % 512;
	}

	bits = msg_len * 8;
	msg[new_len + 0] = (bits >> 56) & 0xFF;
	msg[new_len + 1] = (bits >> 48) & 0xFF;
	msg[new_len + 2] = (bits >> 40) & 0xFF;
	msg[new_len + 3] = (bits >> 32) & 0xFF;
	msg[new_len + 4] = (bits >> 24) & 0xFF;
	msg[new_len + 5] = (bits >> 16) & 0xFF;
	msg[new_len + 6] = (bits >> 8) & 0xFF;
	msg[new_len + 7] = (bits >> 0) & 0xFF;
	new_len += 8;

	for (uint64_t i = 0; i < new_len; i += 64) {
		uint32_t buf[64];

		/* Load the chunk into the first 16 entries of buf */
		for (int j = 0; j < 16; j++) {
			uint64_t k = i + j * 4;
			buf[j] = (msg[k] << 24) | (msg[k + 1] << 16) | (msg[k + 2] << 8) | msg[k + 3];
		}

		/* Extend the first 16 entries into rest of buf */
		for (int j = 16; j < 64; j++) {
			uint32_t s0 = rotr32(buf[j - 15],  7) ^ rotr32(buf[j - 15], 18) ^ (buf[j - 15] >>  3);
			uint32_t s1 = rotr32(buf[j -  2], 17) ^ rotr32(buf[j -  2], 19) ^ (buf[j -  2] >> 10);
			buf[j] = buf[j - 16] + s0 + buf[j - 7] + s1;
		}

		/* Working variables */
		uint32_t A = h0;
		uint32_t B = h1;
		uint32_t C = h2;
		uint32_t D = h3;
		uint32_t E = h4;
		uint32_t F = h5;
		uint32_t G = h6;
		uint32_t H = h7;

		/* --- MAIN LOOP */
		for (int j = 0; j < 64; j++) {
			uint32_t S1 = rotr32(E, 6) ^ rotr32(E, 11) ^ rotr32(E, 25);
			uint32_t ch = (E & F) ^ ((~E) & G);
			uint32_t temp1 = H + S1 + ch + round_constants[j] + buf[j];

			uint32_t S0 = rotr32(A, 2) ^ rotr32(A, 13) ^ rotr32(A, 22);
			uint32_t maj = (A & B) ^ (A & C) ^ (B & C);
			uint32_t temp2 = S0 + maj;

			H = G;
			G = F;
			F = E;
			E = D + temp1;
			D = C;
			C = B;
			B = A;
			A = temp1 + temp2;
		}

		h0 += A;
		h1 += B;
		h2 += C;
		h3 += D;
		h4 += E;
		h5 += F;
		h6 += G;
		h7 += H;
	}

	/* Produce the output */
	uint32_t res[8] = {
		h0, h1, h2, h3, h4, h5, h6, h7
	};

	for (int i = 0; i < 8; i++) {
		uint32_t val = res[i];
		/* Write the value in big-endian */
		for (int j = 4; j; j--) {
			out[i * 4 + j - 1] = val & 0xFF;
			val >>= 8;
		}
	}
	return;
}


char *HCL_sha256(char *msg, uint64_t msg_len) {
	if (msg == NULL) return NULL;

	/* Ensure there's enough space for HCL_sha1_unsafe to pad the message */
	uint64_t mem_len = msg_len + (64 - (msg_len % 64));
	unsigned char *mem = malloc(mem_len);
	if (mem == NULL) return NULL;

	memset(mem, 0, mem_len);
	memcpy(mem, msg, msg_len);

	/* Create the output buffer */
	char *out = malloc(32);
	if (out == NULL) {
		free(mem);
		return NULL;
	}

	HCL_sha256_unsafe(mem, msg_len, out);

	free(mem);
	return out;
}
