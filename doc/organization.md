# Organization

This file aims to provide information regarding the organization of source files.
All paths not beginning with a `/` are relative to the repository root.

## common/

This directory is intended for certain utilities that may be needed for more
than a single algorithm (i.e. *common* ).

For example, things like `rotr32` (rotate right 32-bit), which aren't provided
in the C language but still needed for a lot of algorithms, are implemented in
'common/binary.c' as it is quite commonly needed.

## doc/

This directory holds 'documentation' explaining how this project works, how it is
structured and other things.

## hash/

This directory holds source files for each hash algorithm. If a single algorithm
needs to occupy more than a single source file, please create a directory for it
instead and place all files there.

## include/

This directory holds header files that should be included by any program intending
to use this library. When the (currently non-existent, but planned) installation
script is ran, the headers under this directory will be copied to /usr/include/
by 'install.sh' so that you can include them like this:

`#include <HCL/hash.h>`

## test/

This directory holds all test code for the library. All sources under this
directory will be compiled and linked with the library to form the test
executable, `test.elf`

The test directory has sub-directories for each type of algorithm, e.g.
`test/hash/`
