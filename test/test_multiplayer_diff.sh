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

outdir_player_subject="$outdir/subject"
outdir_player_user="$outdir/user"

mkdir -p $outdir_player_subject
mkdir -p $outdir_player_user

## Set up log file

log_file="$outdir/log.txt"

touch $log_file
echo "Running tests with $@" | tee $log_file

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
	echo "$subject_asm $player_s >$outdir_player_subject/subject_asm_output_$player 2>&1" >> $log_file

	$subject_asm $player_s >$outdir_player_subject/subject_asm_output_$player 2>&1

	subject_asm_exit=$?
	if [ $subject_asm_exit == 0 ]; then
		echo "move $player_cor to $outdir_player_subject" >> $log_file
		mv $player_cor $outdir_player_subject
	else
		echo "$subject_asm exited with $subject_asm_exit" | tee -a $log_file
		exit
	fi

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

## Run players on subject and user VMs

echo "Running VM for $cycles_to_run cycles" >> $log_file

# Run player on VMs; assumes -d and -v flags have been implemented on user as well

run_vm() {
	local corewar=$1
	local player_cor_files=$2
	local output_file=$3
	local vm_verbosity=$4

	echo "$corewar -d $cycles_to_run -v $vm_verbosity $player_cor_files >$output_file 2>&1" >> $log_file
	$corewar $player_cor_files -d $cycles_to_run -v $vm_verbosity >$output_file 2>&1
	exit_status=$?
	if [ $exit_status != 0 ]; then
		echo "$corewar exited with $exit_status; see $output_file" | tee -a $log_file
	fi
}

echo "with subject vm..." >> $log_file

# Form a string with all the subject player .cor files

subject_player_cor_files=""
for var in "$@"
do
	if [[ $var =~ ^[0-9]+$ ]]; then
		continue
	fi
	player_s=$var
	player_cor=$(echo $player_s | sed "s/\.s/\.cor/" | rev | cut -d '/' -f 1 | rev)
	subject_player_cor_files="$subject_player_cor_files $outdir_player_subject/$player_cor"
done

subject_corewar_output_file="$outdir/subject/subject_corewar_output"
run_vm $subject_corewar "-a $subject_player_cor_files" $subject_corewar_output_file 0

echo "with user vm..." >> $log_file

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
run_vm $user_corewar "$user_player_cor_files" $user_corewar_output_file 0

diff_file=$outdir/diff_corewar_output
diff $subject_corewar_output_file $user_corewar_output_file > $diff_file

if [ -s $diff_file ]; then
	echo
	echo "FAILED: Differences found in output files" | tee -a $log_file
	echo
	echo "See $diff_file for details" | tee -a $log_file
	echo
else
	echo
	echo "PASSED" | tee -a $log_file
	echo
fi

subject_corewar_output_file="$outdir/subject/subject_corewar_output"
run_vm $subject_corewar "-a $subject_player_cor_files" $subject_corewar_output_file $vm_verbosity

user_corewar_output_file="$outdir/user/user_corewar_output"
run_vm $user_corewar "$user_player_cor_files" $user_corewar_output_file $vm_verbosity

echo "Test output written to $outdir" | tee -a $log_file
echo

