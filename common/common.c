#include "../include/common.h"

unsigned int rotr32(unsigned int num, int shift) {
	/* 32-bit Rotate Right */
	if ((shift > 32) || (shift < 0)) {
		return 0;
	}
	return (num >> shift) | (num << (32 - shift));
}

unsigned int rotl32(unsigned int num, int shift) {
	/* 32-bit Rotate Left */
	if ((shift > 32) || (shift < 0)) {
		return 0;
	}
	return (num << shift) | (num >> (32 - shift));
}
