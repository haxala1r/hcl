#include "../include/common.h"

uint32_t rotr32(uint32_t num, int shift) {
	/* 32-bit Rotate Right */
	if ((shift > 32) || (shift < 0)) {
		return 0;
	}
	return (num >> shift) | (num << (32 - shift));
}

uint32_t rotl32(uint32_t num, int shift) {
	/* 32-bit Rotate Left */
	if ((shift > 32) || (shift < 0)) {
		return 0;
	}
	return (num << shift) | (num >> (32 - shift));
}

uint64_t rotr64(uint64_t num, int shift) {
	/* 64-bit Rotate Right */
	if ((shift > 64) || (shift < 0)) {
		return 0;
	}
	return (num >> shift) | (num << (64 - shift));
}

uint64_t rotl64(uint64_t num, int shift) {
	/* 64-bit Rotate Left */
	if ((shift > 64) || (shift < 0)) {
		return 0;
	}
	return (num << shift) | (num >> (64 - shift));
}
