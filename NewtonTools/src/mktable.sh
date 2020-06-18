#!/bin/sh

cd $1
for i in *.s 
do
	out=`basename $i .s`.o
	arm-elf-as -EB $i -o $out
done
arm-elf-ar cr ../../lib/$1.a *.o
rm *.o
