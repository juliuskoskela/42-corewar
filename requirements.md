# VM

These tests must be implemented ina  way that they can all be run from the main Makefile.
Checking if the tests passed or failed, must not require manual checking of files or diffs
but the make command has to show a list of passed/failed tests.

## Test module 1: Index wrapping

ld with 516 as first argument loads from offset pc + 4

st with 516 as second argument stores to offset pc + 4

zjmp with 516 jumps to pc + 4

ldi with (lhs + rhs = 516) loads from offset pc + 4

sti with (lhs + rhs = 516) stores to offset pc + 4

fork with 516 starts the forked process at pc + 4

## Test module 2: Index wrapping (negative index)

ld with -516 as first argument loads from offset pc + -4

st with -516 as second argument stores to offset pc + -4

zjmp with -516 jumps to pc + -4

ldi with (lhs + rhs = -516) loads from offset pc + -4

sti with (lhs + rhs = -516) stores to offset pc + -4

fork with -516 starts the forked process at pc + -4

## Test module 3: Champion distribution

Create game with 0 champions or more than 4, must fail.

Create game with 1-4 champions must succeed and champions must be evenly spaced.
For example with 2 champions, the champions should start from 0 and 2048

## Test module 4: Cycles to Die

A process that doesn't do at least one live during CTD number of cycles, must die.

If during a CTD period of time there is at least NBR_LIVE live instructions executed, when
the check-up is executed, CTD must decrease by CYCLE_DELTA.

If during a check-up there has been no CTD since MAX_CHECKS, CTD is decreased by CYCLE_DELTA.

If during a check-up all processes are dead, the game ends. Check-up CAN be done either at
the beginning or at the end of a cycle.

## Test module 5: VM Options

Options that have to be managed

-n (set player number)
-dump (print memory after x cycles and quit)

Errors that have to be managed

- Invalid header
- No code
- Champion too big
- Nameless champion
- Champion with no comment
- Champion with too long name (128)
- Champion with no code

## Test module 6: Basic Match

We must have at least one own champion. It must compile and it would be nice if it could beat
zork.

VM is able to determine the correct winner
