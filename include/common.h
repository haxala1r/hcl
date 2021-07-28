#ifndef HCL_COMMON_H
#define HCL_COMMON_H 1

#include <stdint.h>

/* This file defines some utilities commonly needed by algorithms */

uint32_t rotr32(uint32_t num, int shift);
uint32_t rotl32(uint32_t num, int shift);

uint64_t rotr64(uint64_t num, int shift);
uint64_t rotl64(uint64_t num, int shift);



#endif
