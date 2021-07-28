# haxala1r's Cryptography Library

This is a project aiming to provide secure implementations for cryptographic
(and non-cryptographic) hash functions, encryption algorithms, PRNGs and more.

Despite the name, this library also aims to provide non-cryptographic algorithms
as well.

# Algorithms

Currently provided hash algorithms:

- Murmur3 32-bit
- Jenkin's one at a time
- MD5
- SHA-1
- SHA-256
- SHA-512

# Building & Installing

HCL currently only supports GNU/Linux systems. (NOTE: with a mingw like
environment, it's entirely possible to *build* HCL and link it, but the
installation script just won't work)

You need to have gcc, ld and ar to be able to build and install HCL. Once you
have all of that, you can simply run this command:

`./build.sh ; sudo ./install.sh`

The installation script needs to be run as root. This is due to the fact that
it needs to copy the header files to /usr/include and the library itself to
/usr/lib/

Use `sudo ./uninstall.sh` to uninstall the library.

# Using HCL

Once you've installed HCL, you can include the HCL headers:

`#include <HCL/hash.h>`

... and use one of the declared functions in your code:

`HCL_sha256("ABCD", 4);`

Just keep in mind you need to pass the `-lHCL` parameter to gcc when compiling
your code.

More detailed explanation of what headers and functions are available coming
soon.

# Contributing

I do accept all kinds of contributions. If you see an error, vulnerability, or
just something you'd like seeing added, feel absolutely free to open an issue
or a pull request.

Bear in mind that tests must also be added for each algorithm added.
