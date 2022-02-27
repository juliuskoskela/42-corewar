#!/bin/bash

## By default, this script must be run from within the test folder!

## Paths to our executables
user_asm="../bin/asm"
user_corewar="../bin/corewar"

## Directory to place the result directories in 
result_dir="../test_results"

## Verbosity level for vm: from 0 to 31
vm_verbosity="11"

## Default number of cycles to run before exiting and dumping memory
cycles_to_run=100000

## Path to the player .cor file is taken as the first command line argument

if [ $# -lt 1 ]; then
	echo "usage: bash test_multiplayer_diff.sh path/to/player.s [ path/to/player.s ... ] [ cycles_to_run ]"
	exit 0
fi

## Set up output directory

outdir="$result_dir/output"

for var in "$@"
do
	player_s=$var
	player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")
	outdir=$outdir"_"$player
done

outdir_player_user="$outdir/user"

mkdir -p $outdir_player_user

## Set up log file

log_file="$outdir/log.txt"

touch $log_file
echo "Running with $@" | tee $log_file

## Assemble players

for var in "$@"
do
	if [[ $var =~ ^[0-9]+$ ]]; then
		cycles_to_run=$var
		continue
	fi
	player_s=$var
	player_cor=$(echo $player_s | sed "s/\.s/\.cor/")
	player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")

	echo "Assembling player $player_s" >> $log_file
	echo "$user_asm $player_s >$outdir_player_user/user_asm_output_$player 2>&1" >> $log_file

	$user_asm $player_s >$outdir_player_user/user_asm_output_$player 2>&1

	user_asm_exit=$?
	if [ $user_asm_exit == 0 ]; then
		echo "move $player_cor to $outdir_player_user" >> $log_file
		mv $player_cor $outdir_player_user
	else
		echo "$user_asm exited with $user_asm_exit" | tee -a $log_file
		exit
	fi
done

echo "Running VM for $cycles_to_run cycles" >> $log_file

# Run player on VM; assumes -d and -v flags have been implemented on user_corewar

run_vm() {
	local corewar=$1
	local player_cor_files=$2
	local output_file=$3
	local vm_verbosity=$4

	echo "$corewar -d $cycles_to_run -v $vm_verbosity $player_cor_files >$output_file 2>&1" >> $log_file
	$corewar $player_cor_files -d $cycles_to_run -v $vm_verbosity | tee $output_file 2>&1
	exit_status=$?
	if [ $exit_status != 0 ]; then
		echo "$corewar exited with $exit_status; see $output_file" | tee -a $log_file
	fi
}

# Form a string with all the user player .cor files
user_player_cor_files=""
for var in "$@"
do
	if [[ $var =~ ^[0-9]+$ ]]; then
		continue
	fi
	player_s=$var
	player_cor=$(echo $player_s | sed "s/\.s/\.cor/" | rev | cut -d '/' -f 1 | rev)
	user_player_cor_files="$user_player_cor_files $outdir_player_user/$player_cor"
done

user_corewar_output_file="$outdir/user/user_corewar_output"
run_vm $user_corewar "$user_player_cor_files" $user_corewar_output_file $vm_verbosity

echo "Test output written to $outdir" | tee -a $log_file
echo

