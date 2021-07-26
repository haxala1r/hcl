#include "../include/hash.h"
#include "../include/common.h"
#include <stdlib.h>
#include <string.h>


void HCL_sha1_unsafe(unsigned char *msg, uint64_t msg_len, char *out) {
	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;
	uint32_t h4 = 0xC3D2E1F0;

	/* Padding */
	uint64_t new_len = msg_len;
	msg[new_len++] = 0x80;

	uint64_t bits = new_len * 8 % 512;
	while (bits != 448) {
		msg[new_len++] = 0;

		bits = new_len * 8 % 512;
	}

	bits = msg_len * 8;
	/* Encode the original message length as a 64-bit big endian integer */
	msg[new_len + 0] = (bits >> 56) & 0xFF;
	msg[new_len + 1] = (bits >> 48) & 0xFF;
	msg[new_len + 2] = (bits >> 40) & 0xFF;
	msg[new_len + 3] = (bits >> 32) & 0xFF;
	msg[new_len + 4] = (bits >> 24) & 0xFF;
	msg[new_len + 5] = (bits >> 16) & 0xFF;
	msg[new_len + 6] = (bits >> 8 ) & 0xFF;
	msg[new_len + 7] = (bits >> 0 ) & 0xFF;
	new_len += 8;

	for (uint64_t i = 0; i < new_len; i += 64) {
		/* Load the chunk into the first 16 words of buf*/
		uint32_t buf[80];
		for (int j = 0; j < 16; j++) {
			uint64_t k = i + j * 4;
			buf[j] = (msg[k] << 24);
			buf[j] |= (msg[k + 1] << 16);
			buf[j] |= (msg[k + 2] << 8);
			buf[j] |= (msg[k + 3]);
		}

		/* Extend the loaded chunk to 80 uint32_t's */
		for (int j = 16; j < 80; j++) {
			buf[j] = buf[j - 3] ^ buf[j - 8] ^ buf[j - 14] ^ buf[j - 16];
			buf[j] = rotl32(buf[j], 1);
		}

		/* The hash values for this chunk */
		uint32_t A = h0;
		uint32_t B = h1;
		uint32_t C = h2;
		uint32_t D = h3;
		uint32_t E = h4;

		for (int j = 0; j < 80; j++) {
			uint32_t f, k;
			if (j < 20) {
				f = (B & C) | ((~B) & D);
				k = 0x5A827999;
			} else if (j < 40) {
				f = B ^ C ^ D;
				k = 0x6ED9EBA1;
			} else if (j < 60) {
				f = (B & C) | (B & D) | (C & D);
				k = 0x8F1BBCDC;
			} else if (j < 80) {
				f = B ^ C ^ D;
				k = 0xCA62C1D6;
			}

			uint32_t temp = rotl32(A, 5) + f + E + k + buf[j];
			E = D;
			D = C;
			C = rotl32(B, 30);
			B = A;
			A = temp;
		}

		h0 += A;
		h1 += B;
		h2 += C;
		h3 += D;
		h4 += E;
	}

	uint32_t res[5] = {
		h0, h1, h2, h3, h4
	};

	/* Write each of the hash values as a big-endian integer */
	for (int i = 0; i < 5; i++) {
		uint32_t num = res[i];

		/* This loop ensures it will be written as big-endian regardless of
		 * machine
		 */
		for (int j = 4; j; j--) {
			out[i * 4 + j - 1] = (num & 0xFF);
			num >>= 8;
		}
	}
	return;
}

char *HCL_sha1(char *msg, uint64_t msg_len) {
	if (msg == NULL) return NULL;

	/* Ensure there's enough space for HCL_sha1_unsafe to pad the message */
	uint64_t mem_len = msg_len + (64 - (msg_len % 64));
	unsigned char *mem = malloc(mem_len);
	if (mem == NULL) return NULL;

	memset(mem, 0, mem_len);
	memcpy(mem, msg, msg_len);

	/* Create the output buffer */
	char *out = malloc(20);
	if (out == NULL) {
		free(mem);
		return NULL;
	}

	HCL_sha1_unsafe(mem, msg_len, out);

	free(mem);
	return out;
}
