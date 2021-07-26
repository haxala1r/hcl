#include "../../include/hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* TODO: Add more tests. Currently, these tests aren't stressing it enough.
 * This goes for pretty much all implemented algorithms btw, there's just
 * not enough tests in any of them.
 */

char *sha1_msgs[] = {
	"",
	"ABCD",
	"The quick brown fox jumps over the lazy dog"
};

uint8_t sha1_expected[][20] = {
	{0xda,0x39,0xa3,0xee,0x5e,0x6b,0x4b,0xd,0x32,0x55,0xbf,0xef,0x95,0x60,0x18,0x90,0xaf,0xd8,0x7,0x9},
	{0xfb,0x2f,0x85,0xc8,0x85,0x67,0xf3,0xc8,0xce,0x9b,0x79,0x9c,0x7c,0x54,0x64,0x2d,0xc,0x7b,0x41,0xf6},
	{0x2f,0xd4,0xe1,0xc6,0x7a,0x2d,0x28,0xfc,0xed,0x84,0x9e,0xe1,0xbb,0x76,0xe7,0x39,0x1b,0x93,0xeb,0x12}
};

int test_sha1(void) {
	int test_count = sizeof(sha1_msgs) / sizeof(*sha1_msgs);

	for (int j = 0; j < test_count; j++) {
		char *out = HCL_sha1(sha1_msgs[j], strlen(sha1_msgs[j]));
		if (memcmp(out, sha1_expected[j], 20)) {
			printf("[HCL_sha1] Test failed\n");
			free(out);
			return -1;
		}
		free(out);
	}
	printf("[HCL_sha1] Test passed\n");
	return 0;
}