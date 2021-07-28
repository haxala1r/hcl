#ifndef HCL_HASH_H
#define HCL_HASH_H 1
#include <stdint.h>
#include <stddef.h>

uint32_t HCL_murmur3_32(char *key, int key_len, uint32_t seed);
uint32_t HCL_murmur3_32_seedless(char *key, int key_len);

/* out must be a buffer with at least 16 bytes in it
 * DO NOT USE THE UNSAFE VERSIONS
 * The unsafe ones assume that the message buffer has enough extra space to be
 * padded. If you did not allocate extra space for it, they will attempt to
 * modify out of bounds memory.
 *
 * The regular ones allocate more space for the message so that the unsafe ones can
 * do the work without worrying about bounds. Do *NOT* use the unsafe functions unless
 * you are _really_ concerned about speed (and even then!).
 */
void HCL_md5_unsafe(unsigned char *msg, int msg_len, char *out);
char *HCL_md5(char *msg, int msg_len);

void HCL_sha1_unsafe(unsigned char *msg, uint64_t msg_len, char *out);
char *HCL_sha1(char *msg, uint64_t msg_len);

void HCL_sha256_unsafe(unsigned char *msg, uint64_t msg_len, char *out);
char *HCL_sha256(char *msg, uint64_t msg_len);

void HCL_sha512_unsafe(unsigned char *msg, uint64_t msg_len, char *out);
char *HCL_sha512(char *msg, uint64_t msg_len);

uint32_t HCL_joaat(char *key, int key_len);

#endif
