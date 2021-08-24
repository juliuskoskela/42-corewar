#!/bin/bash

executable="../asm"
test_dir="asm_test_error_files"

for file in $test_dir/*
do
	echo "Test $executable $file:"
	$executable $file
	echo ""
done
