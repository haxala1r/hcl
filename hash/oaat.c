#include "../include/common.h"
#include "../include/hash.h"

/* This file implements the one-at-a-time hash function, designed by Bob Jenkins
 * This is a rather simple and fast hash function, most suitable for hash tables
 * and unsuitable for cryptographic purposes.
 */

uint32_t HCL_joaat(char *key, int key_len) {
	uint32_t hash = 0;

	for (int i = 0; i < key_len; i++) {
		hash += key[i];
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}
