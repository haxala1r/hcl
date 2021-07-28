#!/bin/sh

# The only requirements are:
#  - Have GCC, LD and AR installed.

# The object files for the library.
export LIBOBJ=""
export LIBDIRS="hash common"

# The object files for the test program.
export TESTOBJ=""
export TESTDIRS="test"


export CFLAGS="-O3 -std=c99 -Wall -Wextra -pedantic"

# Combile the library sources.
for DIR in $LIBDIRS
do
	for FILE in $(find ./${DIR}/* -name "*.c")
	do
		gcc -c "${FILE}" -o "${FILE%.c}.o" ${CFLAGS}
		LIBOBJ="${LIBOBJ} ${FILE%.c}.o"
	done
done

# Compile the test files.
for DIR in $TESTDIRS
do
	for FILE in $(find ./${DIR}/* -name "*.c")
	do
		gcc -c "${FILE}" -o "${FILE%.c}.o" ${CFLAGS}
		TESTOBJ="${TESTOBJ} ${FILE%.c}.o"
	done
done

# Create the library
ar rcs "libHCL.a" ${LIBOBJ}

# Build the test program.
gcc ${TESTOBJ} libHCL.a -o test.elf
