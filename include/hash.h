#ifndef HCL_HASH_H
#define HCL_HASH_H 1
#include <stdint.h>
#include <stddef.h>

uint32_t HCL_murmur3_32(char *key, int key_len, uint32_t seed);
uint32_t HCL_murmur3_32_seedless(char *key, int key_len);


#endif
