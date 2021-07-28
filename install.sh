#!/bin/sh

# This needs to be run as root.

# Copy the archive
cp libHCL.a /usr/lib/

# Copy the header files
mkdir -p /usr/include/HCL/
cp include/* /usr/include/HCL

echo "Installation successful"
