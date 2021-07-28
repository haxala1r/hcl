# Build System

Currently, HCL relies on shell scripts for building and installation.

## build.sh

This script builds the entire library (as well as tests) and outputs two files:
`libHCL.a` and `test.elf`

libHCL.a is the library archive. This is the file to be linked to your executable.
It's created by compiling every source file in the repository, *except those under
test/* and using `ar` to create the archive.

test.elf is the test executable, which runs all tests available on the library,
and outputs their results to stdout.

## clean.sh

This script cleans all build files in the repository (that were created by build.sh)

Note that this does NOT uninstall the library. Use uninstall.sh

## install.sh

Installs the library to your system.

In a bit more detail: it simply copies 'libHCL.a' tp /usr/lib/ and it copies
all headers under include/ into /usr/include/HCL/

## uninstall.sh

Uninstalls the library. Deletes /usr/lib/libHCL.a and /usr/include/HCL/

