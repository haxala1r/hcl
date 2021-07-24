#include "../../include/hash.h"
#include <stdio.h>

int test_joaat(void) {
	char key[16] = "ABCDEFGHIJKLMNO";
	if (HCL_joaat(key, 15) == 0xE7FFD6E7) {
		printf("[HCL_joaat] Test passed\n");
		return 0;
	}
	printf("HCL_joaat returned '%u' expected '%u'\n", HCL_joaat(key, 15), 0xE7FFD6E7);
	return -1;
}
