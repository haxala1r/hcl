#include "../include/common.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <string.h>

uint32_t HCL_murmur3_32(char *key, int key_len, uint32_t seed) {
	if (key == NULL) return 0;
	if (key_len <= 0) return 0;

	uint32_t k;
	uint32_t hash = seed;

	/* --- BODY */
	for (int i = key_len>>2; i > 0; i--) {
		/* Get the current four byte chunk into k
		 * The loop is so that it still works on big endian machines as well.
		 */

		k = 0;
		for (int j = 4; j; j--) {
			k <<= 8;
			k |= key[j - 1];
		}
		key += 4;

		/* Scramble k */
		k *= 0xcc9e2d51;
		k = rotl32(k, 15);
		k *= 0x1b873593;

		hash ^= k;
		hash = rotl32(hash, 13);
		hash = (hash * 5) + 0xe6546b64;
	}

	/* --- TAIL */
	k = 0;
	for (int i = (key_len & 3); i; i--) {
		k <<= 8;
		k |= key[i - 1];
	}

	/* Scramble again */
	k *= 0xcc9e2d51;
	k = rotl32(k, 15);
	k *= 0x1b873593;

	hash ^= k;

	/* Finalization. */
	hash ^= key_len;

	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}

uint32_t HCL_murmur3_32_seedless(char *key, int key_len) {
	/* contrary to what the name suggests, this simply supplies rand() as seed */
	return HCL_murmur3_32(key, key_len, rand());
}
