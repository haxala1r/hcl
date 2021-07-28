#!/bin/sh

for F in $(find ./* -name "*.o")
do
	rm "${F}"
done

rm *.a
rm *.elf
