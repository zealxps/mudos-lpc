#!/bin/bash

output=$1

rm $output
for f in `find . -name "*.c" | xargs grep UTEST | cut -d ":" -f 1 | uniq `; do
	echo ${f:2} >> $output
done
	
