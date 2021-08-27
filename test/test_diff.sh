#!/bin/bash

## Paths to subject's and our executables
subject_asm="./vm_champs/asm"
subject_corewar="./vm_champs/corewar"
user_asm="../bin/asm"
user_corewar="../bin/corewar"

## Verbosity level for vm: from 0 to 31
vm_verbosity="31"

## Path to the player .cor file is taken as the first command line argument

if [ $# -lt 1 ]; then
	echo "usage: bash test_diff.sh path/to/player.s [ cycles_to_run ]"
	exit 0
fi

echo
echo "Running tests with $1"

player_s=$1
player_cor=$(echo $player_s | sed "s/\.s/\.cor/")
player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")

## Set up output directory

outdir="output_$player"
outdir_subject="$outdir/subject"
outdir_user="$outdir/user"

echo
echo "Creating output directory $outdir"
mkdir -p $outdir $outdir_user $outdir_subject

## Assemble player on subject and user asm, redirect all output to files

echo
echo "Assembling player $player_s"

assemble_player() {
	local asm=$1
	local output_dir=$2
	local output_filename=$3
	local output_file=$output_dir/$output_filename

	echo "$asm $player_s >$output_file 2>&1"
	$asm $player_s >$output_file 2>&1
	exit_status=$?
	if [ $exit_status == 0 ]; then
		echo "move $player_cor to $output_dir"
		mv $player_cor $output_dir
	else
		echo "$asm exited with $exit_status; see $output_file"
	fi
}

echo
echo "with subject asm..."
assemble_player $subject_asm $outdir_subject subject_asm_output_$player

echo
echo "with user asm..."
assemble_player "$user_asm -v" $outdir_user user_asm_output_$player

## Run player on subject and user VMs

# If a second command line argument is given, use that as the number of
# cycles after which to dump output. Otherwise use a default value

if [ $# -ge 2 ]; then
	cycles_to_run=$2
else
	cycles_to_run=50
fi

echo
echo "Running VM for $cycles_to_run cycles"

# Run player on VMs; assumes -d and -v flags have been implemented on user as well

run_vm() {
	local corewar=$1
	local player_cor=$2
	local output_file=$3

	echo "$corewar $player_cor -d $cycles_to_run -v $vm_verbosity >$output_file 2>&1"
	$corewar $player_cor -d $cycles_to_run -v $vm_verbosity >$output_file 2>&1
	exit_status=$?
	if [ $exit_status != 0 ]; then
		echo "$corewar exited with $exit_status; see $output_file"
	fi
}

echo
echo "with subject vm..."
subject_player_cor="$outdir_subject/$player.cor"
subject_corewar_output_file="$outdir_subject/subject_corewar_output_$player"
run_vm $subject_corewar $subject_player_cor $subject_corewar_output_file

echo
echo "with user vm..."
user_player_cor="$outdir_user/$player.cor"
user_corewar_output_file="$outdir_user/user_corewar_output_$player"
run_vm $user_corewar $user_player_cor $user_corewar_output_file

## Take diff

diff $subject_corewar_output_file $user_corewar_output_file > $outdir/diff_corewar_output_$player

echo
echo "Test output written to $outdir"
echo
