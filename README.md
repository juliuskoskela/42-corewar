# Summary of the project subject

> Corewar is a very peculiar game. It’s about bringing “players” together around a“virtual machine”, which will load some “champions” who will fight against one an-other with the support of “processes”, with the objective being for these championsto stay “alive”.
>
> The processes are executed sequentially within the same virtual machine and mem-ory space. They can therefore, among other things, write and rewrite on top ofeach others so to corrupt one another, force the others to execute instructions thatcan damage them,</br> try to rewrite on the go the coding equivalent of aCôtes duRhône 1982(that is one delicious French wine!), etc...
>
> The game ends when all the processes are dead.  The winner is the last player reported to be “alive”.

The project consists of three parts: an assembler (a compiler), a virtual machine and a champion.

## The assembler (``asm``): Compiles champion programs from assembly to bytecode

```
./asm mychampion.s
```

- reads the assembly code from the file with a suffix ``.s`` given as argument, parses it into a bytecode format that it then writes to a file with the same name as the argument but with the suffix ``.cor``
- in case of error, writes an error message to stderr



## The virtual machine (``corewar``): Interprets and executes the compiled champions sequentially

```
./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
```

- in case of error, writes an error message to stderr
- big endian
- "for implementation purposes, we will suppose that each instruction willexecute itself (completely) at the end of its last cycle and wait for its entire duration.The instructions ending at the same cycle will execute themselves in in decreasingorder of the processes’ number. -- (youngest) champion plays first."


## The champion

- with ``.s`` suffix, written in assembly, has the objective of its process staying "alive" throughout the VM's execution
- this is achieved by reporting as "alive" and eradicating its opponents


## The assembly language

- composed of one instruction per line, instructions take the format of ``[label] opcode parameters``, where
  - optional label is composed of a string of characters from LABEL_CHARS followed by LABEL_CHAR
    - can have no instruction following it or be placed on a line before the instruction
  - opcode (valid opcodes listed below)
  - parameters, separated by SEPARATOR_CHAR,</br> that have three types:
    - registry T_REG: rx where x = REG_NUMBER
    - direct T_DIR: DIRECT_CHAR followed by a numeric value or a label (preceded by LABEL_CHAR) that represents a direct value
    - indirect T_IND: a value or a label (preceded by LABEL_CHAR) that represents a value located at the address of the parameter (relative to the PC of the current process)
- comments start with COMMENT_CHAR
- champion's name and description on lines following NAME_CMD_STRING and COMMENT_CMD_STRING, respectively

- valid opcodes:

opcode (hex) | mnemonic | name | no of params : { params } | acb | no of cycles | example & description
-- | -- | -- | -- | -- | -- | --
1 (0x01) | ``live`` | "alive" | 1 : { T_DIR } | no | 10 | ``live id`` </br> Reports player #id as being alive
2 (0x02) | ``ld`` | "load" | 2 : { T_DIR \| T_IND,</br> T_REG } | yes | 5 | ``ld src, dst`` </br> Loads src in register dst, value of src affects zf
13 (0x0d) | ``lld`` | "long load" | 2 : { T_DIR \| T_IND,</br> T_REG } | yes | 10 | ``lld src, dst`` </br> Long version of ld
10 (0x0a) | ``ldi`` | "load index" | 3 : { T_REG \| T_DIR \| T_IND,</br> T_DIR \| T_REG,</br> T_REG } | yes | 25 | ``ldi lhs, rhs, dst`` </br> Computes lhs + rhs and uses the result as an offset to address memory and load a 32-bit value into the register dst.
14 (0x0e) | ``lldi`` | "long load index" | 3 : { T_REG \| T_DIR \| T_IND,</br> T_DIR \| T_REG,</br> T_REG } | yes | 50 | ``lldi lhs, rhs, dst`` </br> The long version of ldi. Neither the parameter values nor the computed address will have their reach limited. Contrary to ldi, the value loaded from memory affects zf.
3 (0x03) | ``st`` | "store" | 2 : { T_REG,</br> T_IND \| T_REG } | yes | 5 | ``st src, dst`` </br> Stores value of registry src in dst
11 (0x0b) | ``sti`` | "store index" | 3 : { T_REG,</br> T_REG \| T_DIR \| T_IND,</br> T_DIR \| T_REG } | yes | 25 | ``sti src, lhs, rhs`` </br> Computes lhs + rhs and uses the result as an offset to address memory and store the value of the register src at that memory location.
4 (0x04) | ``add`` | "addition" | 3 : { T_REG,</br> T_REG,</br> T_REG } | yes | 10 | ``add lhs, rhs, dst`` </br> Computes lhs + rhs and and stores the result in register dst. Result affects zf
5 (0x05) | ``sub`` | "subtraction" | 3 : { T_REG,</br> T_REG,</br> T_REG } | yes | 10 | ``sub lhs, rhs, dst`` </br> Computes lhs - rhs and and stores the result in register dst. Result affects zf
6 (0x06) | ``and`` | "and: r1 & r2 -> r3" | 3 : { T_REG \| T_DIR \| T_IND,</br> T_REG \| T_IND \| T_DIR,</br> T_REG } | yes | 6 | ``and lhs, rhs, dst`` </br> Computes lhs & rhs and and stores the result in register dst. Result affects zf
7 (0x07) | ``or`` | "or: r1 \| r2 -> r3" | 3 : { T_REG \| T_DIR \| T_IND,</br> T_REG \| T_IND \| T_DIR,</br> T_REG } | yes | 6 | ``or lhs, rhs, dst`` </br> Computes lhs \| rhs and and stores the result in register dst. Result affects zf
8 (0x08) | ``xor`` | "xor: r1 ^ r2 -> r3" | 3 : { T_REG \| T_DIR \| T_IND,</br> T_REG \| T_IND \| T_DIR,</br> T_REG } | yes | 6 | ``xor lhs, rhs, dst`` </br> Computes lhs ^ rhs and and stores the result in register dst. Result affects zf
9 (0x09) | ``zjmp`` | "jump if zero" | 1 : { T_DIR } | no | 20 | ``zjmp offset`` </br> Moves the process's PC by offset only if the process's zf is set to 1
12 (0x0c) | ``fork`` | "fork" | 1 : { T_DIR } | no | 800 | ``fork offset`` </br> Forks this process: effectively creates a new process that inherits the current process' registers and zf. The spawned process has its PC set to his parent's PC offseted by offset.
15 (0x0f) | ``lfork`` | "long fork" | 1 : { T_DIR } | no | 1000 | ``lfork offset`` </br> Long version of fork
16 (0x10) | ``aff`` | "aff" | 1 : { T_REG } | yes | 2 | ``aff chr`` </br> Makes this process' champion talk by displaying chr's value. This instruction is useful if you want to ridicule your opponents.

- any other codes have the effect of passing to the next one and losing a cycle

## Instructions

live id | ⏱10

Reports this process and the player #id as being alive.

ld src, dst | ⏱5

Loads src in the register dst. src's value affects zf.

st src, dst | ⏱5

Stores src's register value in dst (either a register or a memory location).

add lhs, rhs, dst | ⏱10

Computes lhs + rhs and stores the result in the register dst. The result affects zf.

sub lhs, rhs, dst | ⏱10

Computes lhs - rhs and stores the result in the register dst. The result affects zf.

and lhs, rhs, dst | ⏱6

Computes lhs & rhs and stores the result in the register dst. The result affects zf.

or lhs, rhs, dst | ⏱6

Computes lhs | rhs and stores the result in the register dst. The result affects zf.

xor lhs, rhs, dst | ⏱6

Computes lhs ^ rhs and stores the result in the register dst. The result affects zf.

zjmp offset | ⏱20

Moves the process' pc by offset only if the process' zf is set to 1.

ldi lhs, rhs, dst | ⏱25

Computes lhs + rhs and uses the result as an offset to address memory and load a 32bit value into the register dst.

sti src, lhs, rhs | ⏱25

Computes lhs + rhs and uses the result as an offset to address memory and store the value of the register src at that memory location.

fork offset | ⏱800

Forks this process. This effectively creates a new process that inherits the current process' registers and zf. The spawned process has its pc set to his parent's pc offseted by offset.

lld src, dst | ⏱10

The long version of ld.

lldi lhs, rhs, dst | ⏱50

The long version of ldi. Neither the parameter values nor the computed address will have their reach limited. Contrary to ldi, the value loaded from memory affects zf.

lfork offset | ⏱1000

The long version of fork

aff chr | ⏱2 (not yet implemented, subject to change)

Makes this process' champion talk by displaying chr's value. This instruction is useful if you want to ridicule your opponents.
