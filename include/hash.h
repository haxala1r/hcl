#ifndef HCL_HASH_H
#define HCL_HASH_H 1
#include <stdint.h>
#include <stddef.h>

uint32_t HCL_murmur3_32(char *key, int key_len, uint32_t seed);
uint32_t HCL_murmur3_32_seedless(char *key, int key_len);

/* out must be a buffer with at least 16 bytes in it
 * DO NOT USE HCL_md5_unsafe (see hash/md5.c line 29)
 */

void HCL_md5_unsafe(unsigned char *msg, int msg_len, char *out);
void HCL_md5(char *msg, int msg_len, char *out);

uint32_t HCL_joaat(char *key, int key_len);

#endif
