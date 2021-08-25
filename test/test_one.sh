#!/bin/bash

## Paths to executables
user_asm="../bin/asm"
user_corewar="../bin/corewar"

## Verbosity level for vm: from 0 to 31
vm_verbosity="31"

## Path to the player .cor file is taken as the first command line argument

if [ $# -lt 1 ]; then
	echo "usage: bash test_one.sh path/to/player.s [ cycles_to_run ]"
	exit 0
fi

echo "Running tests with $1"

player_s=$1
player_cor=$(echo $player_s | sed "s/\.s/\.cor/")
player=$(echo $player_s | rev | cut -d '/' -f 1 | rev | sed "s/\.s//")

## Set up output directory

outdir="output_one_$player"

echo
echo "Creating output directory $outdir"
mkdir -p $outdir

## Assemble player on user asm, redirect all output to files

echo
echo "Assembling player $player_s"

$user_asm $player_s >$outdir/user_asm_output 2>&1

user_asm_exit=$?
if [ $user_asm_exit == 0 ]; then
	echo "move $player_cor to $outdir"
	mv $player_cor $outdir
else
	echo "$user_asm exited with $user_asm_exit"
	exit
fi

## Run player on user VM

# If a second command line argument is given, use that as the number of
# cycles after which to dump output. Otherwise use a default value

if [ $# -ge 2 ]; then
	cycles_to_run=$2
else
	cycles_to_run=50
fi

echo
echo "Running VM for $cycles_to_run cycles"

user_player_cor="$outdir/$player.cor"

# Assumes that flags -dump and -v have been implemented

$user_corewar $user_player_cor -dump $cycles_to_run -v $vm_verbosity >$outdir/user_corewar_output 2>&1

user_corewar_exit=$?
if [ $user_corewar_exit != 0 ]; then
	echo "$user_corewar exited with $user_corewar_exit"
fi

## Done

echo
echo "Test output written to $outdir"
