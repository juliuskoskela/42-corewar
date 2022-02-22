#!/bin/bash

## By default, this script must be run from within the test folder!

## Paths to subject's and our executables
subject_asm="./subject_reference/asm"
subject_corewar="./subject_reference/corewar"
user_asm="../bin/asm"
user_corewar="../bin/corewar"

## Directory to place the result directories in 
result_dir="../test_results"

## Verbosity level for vm: from 0 to 31
vm_verbosity="31"

## Number of cycles to run before exiting and dumping memory
cycles_to_run=1535

## Path to the player .cor file is taken as the first command line argument

if [ $# -lt 1 ]; then
	echo "usage: bash test_single_player_diff.sh path/to/player.s [ cycles_to_run ]"
	exit 0
fi

player_s=$1
player_cor=$(echo $player_s | sed "s/\.s/\.cor/")
player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")

## Set up output directory

outdir="$result_dir/output_$player"
outdir_subject="$outdir/subject"
outdir_user="$outdir/user"

mkdir -p $outdir $outdir_user $outdir_subject

## Log file to write to

log_file="$outdir/log.txt"

touch $log_file
echo "Running tests with $1" | tee $log_file

## Assemble player on subject and user asm, redirect all output to files

echo "Assembling player $player_s" >> $log_file

assemble_player() {
	local asm=$1
	local output_dir=$2
	local output_filename=$3
	local output_file=$output_dir/$output_filename

	echo "$asm $player_s >$output_file 2>&1" >> $log_file
	$asm $player_s >$output_file 2>&1
	exit_status=$?
	if [ $exit_status == 0 ]; then
		echo "move $player_cor to $output_dir" >> $log_file
		mv $player_cor $output_dir
	else
		echo "$asm exited with $exit_status; see $output_file"
	fi
}

echo "with subject asm..." >> $log_file
assemble_player $subject_asm $outdir_subject subject_asm_output_$player

echo "with user asm..." >> $log_file
assemble_player "$user_asm -v" $outdir_user user_asm_output_$player

## Run player on subject and user VMs

# If a second command line argument is given, use that as the number of
# cycles after which to dump output. Otherwise use a default value

if [ $# -ge 2 ]; then
	cycles_to_run=$2
fi

echo "Running VM for $cycles_to_run cycles" >> $log_file

# Run player on VMs; assumes -d and -v flags have been implemented on user as well

run_vm() {
	local corewar=$1
	local player_cor=$2
	local output_file=$3
	local vm_verbosity=$4

	echo "$corewar -d $cycles_to_run -v $vm_verbosity $player_cor >$output_file 2>&1" >> $log_file
	$corewar $player_cor -d $cycles_to_run -v $vm_verbosity >$output_file 2>&1
	exit_status=$?
	if [ $exit_status != 0 ]; then
		echo "$corewar exited with $exit_status; see $output_file"
	fi
}

echo "with subject vm..." >> $log_file

subject_player_cor="$outdir_subject/$player.cor"
subject_corewar_output_file="$outdir_subject/subject_corewar_output_$player"
run_vm $subject_corewar "-a $subject_player_cor" $subject_corewar_output_file 0

echo "with user vm..." >> $log_file
user_player_cor="$outdir_user/$player.cor"
user_corewar_output_file="$outdir_user/user_corewar_output_$player"
run_vm $user_corewar $user_player_cor $user_corewar_output_file 0

diff_file=$outdir/diff_corewar_output_$player
diff $subject_corewar_output_file $user_corewar_output_file > $diff_file

if [ -s $diff_file ]; then
	echo
	echo "FAILED: Differences found in output files"
	echo
	echo "See $diff_file for details"
	echo
else
	echo
	echo "PASSED"
	echo
fi

subject_player_cor="$outdir_subject/$player.cor"
subject_corewar_output_file="$outdir_subject/subject_corewar_output_$player"
run_vm $subject_corewar "-a $subject_player_cor" $subject_corewar_output_file $vm_verbosity

user_player_cor="$outdir_user/$player.cor"
user_corewar_output_file="$outdir_user/user_corewar_output_$player"
run_vm $user_corewar $user_player_cor $user_corewar_output_file $vm_verbosity

## Take diff

echo "Test output written to $outdir"
echo

