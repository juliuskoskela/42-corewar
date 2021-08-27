#!/bin/bash

executable="../asm"
test_dir="asm_test_valid_files"

echo
echo "Testing asm with .s files in $test_dir"
echo

for file in $test_dir/*.s
do
	echo "Test: $executable $file"
	$executable $file
	echo ""
done
