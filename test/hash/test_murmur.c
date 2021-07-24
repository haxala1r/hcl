#include "../../include/hash.h"
#include <stdio.h>


int test_murmur3(void) {
	char key[16] = "ABCDEFGHIJKLMNO";

	if (HCL_murmur3_32(key, 15, 0) == (unsigned int)1122877696) {
		printf("[HCL_murmur3_32] Test passed\n");
		return 0;
	}
	printf("HCL_murmur3_32 returned '%u' expected '%u'\n", HCL_murmur3_32(key, 15, 0), 1122877696);
	return -1;
}
