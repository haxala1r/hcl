#include "../include/hash.h"
#include "../include/common.h"
#include <string.h>
#include <stdlib.h>


/* These can be computed at runtime, but it would be rather slow to compute
 * them _every time_ this function is called, so I'm simply hardcoding them
 */
uint32_t K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1,   0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942,  0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97,  0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d,   0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

/* The per-round shift amounts. short int, so as to not waste space */
short int shift[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};


/* DO NOT USE THIS DIRECTLY UNLESS YOU HAVE A GOOD REASON TO.
 * This function assumes that the message has enough extra space to be padded
 * to a multiple of 512 bits. If you did not allocate extra space for it,
 * this function will attempt to modify out of bounds memory.
 *
 * HCL_md5 allocates more space for the message so that HCL_md5_unsafe can
 * do the work without worrying about bounds. Do *NOT* use HCL_md5_unsafe unless
 * you are _really_ concerned about speed (and even then!).
 */
void HCL_md5_unsafe(unsigned char *msg, int msg_len, char *out) {
	/* This function works with bytes, msg_len should also be in bytes */

	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	int new_len = msg_len;
	msg[new_len++] = 0x80; /* Append a one and 7 zeroes */

	uint64_t bits = new_len * 8 % 512;
	while (bits != 448) {
		msg[new_len++] = 0;

		bits = new_len * 8 % 512;
	}

	/* append the original length in bits, little endian (this will work on either
	 * endianness)
	 */
	bits = msg_len * 8;
	msg[new_len + 0] = (bits >> 0) & 0xFF;
	msg[new_len + 1] = (bits >> 8) & 0xFF;
	msg[new_len + 2] = (bits >> 16) & 0xFF;
	msg[new_len + 3] = (bits >> 24) & 0xFF;
	msg[new_len + 4] = (bits >> 32) & 0xFF;
	msg[new_len + 5] = (bits >> 40) & 0xFF;
	msg[new_len + 6] = (bits >> 48) & 0xFF;
	msg[new_len + 7] = (bits >> 56) & 0xFF;
	new_len += 8;

	for (int i = 0; i < new_len; i += 64) {
		/* Break the 512-bit chunk into 16 4-byte integers */
		uint32_t chunk[16];
		for (int j = 0; j < 16; j++) {
			int k = i + j * 4;
			chunk[j] = msg[k] | (msg[k + 1] << 8) | (msg[k + 2] << 16) | (msg[k + 3] << 24);
		}

		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;

		/* --- MAIN LOOP */
		for (int j = 0; j < 64; j++) {
			uint32_t F, g;
			if (j < 16) {
				F = (B & C) | ((~B) & D);
				g = j;
			} else if (j < 32) {
				F = (D & B) | ((~D) & C);
				g = (5 * j + 1) % 16;
			} else if (j < 48) {
				F = B ^ C ^ D;
				g = (3 * j + 5) % 16;
			} else {
				F = C ^ (B | (~D));
				g = (7 * j) % 16;
			}

			F += A + K[j] + chunk[g];
			A = D;
			D = C;
			C = B;
			B += rotl32(F, shift[j]);
		}

		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}

	uint32_t output[4] = {
		a0, b0, c0, d0
	};

	for (int i = 0; i < 4; i++) {
		/* Write each of the integers to the output buffer in little endian order*/
		uint32_t num = output[i];
		for (int j = 0; j < 4; j++) {
			out[i * 4 + j] = (char)(num & 0xFF);
			num >>=8;
		}
	}

	return;
}

void HCL_md5(char *msg, int msg_len, char *out) {
	if (msg == NULL) return;
	if (msg_len < 0) return;
	if (out == NULL) return;

	/* Create enough space so that HCL_md5_unsafe has enough space to pad it */
	int mem_len = msg_len + (64 - (msg_len % 64));

	unsigned char *mem = malloc(mem_len);
	if (mem == NULL) return;

	memset(mem, 0, mem_len);
	memcpy(mem, msg, msg_len);

	/* Let HCL_md5_unsafe do its work */
	HCL_md5_unsafe(mem, msg_len, out);

	/* free the extra memory and return */
	free(mem);
	return;
}
