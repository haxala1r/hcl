#include "../../include/hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* TODO: Add more tests. Currently, these tests aren't stressing it enough.
 * This goes for pretty much all implemented algorithms btw, there's just
 * not enough tests in any of them.
 */


char *md5_msgs[] = {
	"",
	"ABCD",
	"The quick brown fox jumps over the lazy dog"
};

uint8_t md5_expected[][16] = {
	{0xd4,0x1d,0x8c,0xd9,0x8f,0x00,0xb2,0x04,0xe9,0x80,0x09,0x98,0xec,0xf8,0x42,0x7e},
	{0xcb,0x08,0xca,0x4a,0x7b,0xb5,0xf9,0x68,0x3c,0x19,0x13,0x3a,0x84,0x87,0x2c,0xa7},
	{0x9e,0x10,0x7d,0x9d,0x37,0x2b,0xb6,0x82,0x6b,0xd8,0x1d,0x35,0x42,0xa4,0x19,0xd6}
};

int test_md5(void) {
	int test_count = sizeof(md5_msgs) / sizeof(*md5_msgs);

	for (int i = 0; i < test_count; i++) {
		char *saw = HCL_md5(md5_msgs[i], strlen(md5_msgs[i]));
		if (memcmp(md5_expected[i], saw, 16)) {
			printf("[HCL_md5]Test failed for '%s'\n", md5_msgs[i]);
			free(saw);
			return -1;
		}
		free(saw);
	}
	printf("[HCL_md5] Test passed\n");
	return 0;
}
