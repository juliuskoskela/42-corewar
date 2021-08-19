#!/bin/bash

## Paths to subject's and our executables

subject_asm="./vm_champs/asm"
subject_corewar="./vm_champs/corewar"
user_asm="../bin/asm"
user_corewar="../bin/corewar"

## Path to the player .cor file is taken as the first command line argument

if [ $# -lt 1 ]; then
	echo "usage: bash test_diff.sh path/to/player.s [ cycles_to_run ]"
	exit 0
fi

echo "Running tests with $1"

player_s=$1
player_cor=$(echo $player_s | sed "s/\.s/\.cor/")
player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")

## Set up output directory

outdir="output_$player"
outdir_subject="$outdir/subject"
outdir_user="$outdir/user"

echo "Creating output directory $outdir"

mkdir -p $outdir $outdir_user $outdir_subject

## Assemble player on subject and user asm, redirect all output to files

echo "Assembling player $player_s"

# Subject

$subject_asm $player_s >$outdir_subject/subject_asm_output 2>&1

subject_asm_exit=$?
if [ $subject_asm_exit == 0 ]; then
	mv $player_cor $outdir_subject
else
	echo "$subject_asm exited with $subject_asm_exit"
fi

# User

$user_asm $player_s >$outdir_user/user_asm_output 2>&1

user_asm_exit=$?
if [ $user_asm_exit == 0 ]; then
	mv $player_cor $outdir_user
else
	echo "$user_asm exited with $user_asm_exit"
fi

if [ $subject_asm_exit != 0 ] && [ $user_asm_exit != 0 ]; then
	echo "Test output written to $outdir_user and $outdir_subject"
	exit
fi

## Run player on subject and user VMs

# If a second command line argument is given, use that as the number of
# cycles after which to dump output. Otherwise use a default value

if [ $# -ge 2 ]; then
	cycles_to_run=$2
else
	cycles_to_run=50
fi

echo "Running VM for $cycles_to_run cycles"

# Subject

subject_player_cor="$outdir_subject/$player.cor"

$subject_corewar $subject_player_cor -d $cycles_to_run -v 31 >$outdir_subject/subject_corewar_output 2>&1

subject_corewar_exit=$?
if [ $subject_corewar_exit != 0 ]; then
	echo "$subject_corewar exited with $subject_corewar_exit"
fi

# User

user_player_cor="$outdir_user/$player.cor"

$user_corewar $user_player_cor -dump $cycles_to_run >$outdir_user/user_corewar_output 2>&1

user_corewar_exit=$?
if [ $user_corewar_exit != 0 ]; then
	echo "$user_corewar exited with $user_corewar_exit"
fi

## Done

echo "Test output written to $outdir_user and $outdir_subject"
