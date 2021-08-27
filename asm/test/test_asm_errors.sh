#!/bin/bash

executable="../asm"
test_dir="asm_test_error_files"

echo
echo "Testing asm with all files in $test_dir"
echo

for file in $test_dir/*
do
	echo "Test: $executable $file"
	$executable $file
	echo ""
done
