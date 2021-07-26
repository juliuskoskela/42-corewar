#!/bin/bash

executable="subject_asm"
test_dir="asm_test_files"

for file in $test_dir/*.s
do
	echo "Test ./$executable $file:"
	./$executable $file
	echo ""
done
