#!/bin/sh

for F in $(find ./* -name "*.o")
do
	rm "${F}"
done

rm libhcl.a
rm test.elf
