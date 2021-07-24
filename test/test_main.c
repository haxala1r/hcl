#include "include/hash.h"
#include <stdio.h>


/* This is the main file of the test program. */

/* This is a global array, keeping a list of all tests.
 * The main program loops over this and runs each test.
 * If any fails, it should print an error message AND return -1.
 */

int (*test_arr[])(void) = {
	test_murmur3
};



int main(void) {
	int test_count = sizeof(test_arr) / sizeof(*test_arr);

	for (int i = 0; i < test_count; i++) {
		if (test_arr[i]()) {
			printf("A test failed.\n");
			return -1;
		}
	}
	printf("All tests passed\n");
	return 0;
}
