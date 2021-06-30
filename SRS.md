# Corewar - Software Requirement Specifications

## Repository Structure

```

corewar
-- inc
-- lib
-- mod
---- asm
------ inc
------ src
------ README
------ Makefile
---- vm
------ inc
------ src
------ README
------ Makefile
---- gui
------ inc
------ src
------ assets
------ README
------ Makefile
---- test
------ inc
------ src
------ Makefile
-- doc
-- pic
-- Makefile
-- README
-- author

```

## Requirements

What this program should be able to do.

## Usage

How this program is supposed to be used, including flags and examples about how
to pipe or otherwise combine the programs to achieve desired output if
applicable.

## Modules

### Asm Module

Module for interpreting and processing the assembly instructions detailed in the
subject.

Target: asm
Namespace: asm_

```

asm
-- inc
-- src
-- README
-- Makefile

```

Details: Link to SRS_MOD_ASM

### Virtual Machine Module

Module for creating the virtual machine environment for the champion arena.

Target: corewar
namespace: vm_

```

corewar
-- inc
-- src
-- README
-- Makefile

```

Details: Link to SRS_MOD_VM

### Graphical Interface Module

Module for creating a graphcial user interface for the game.

Target: gui.a
namespace: gui

```

gui
-- inc
-- src
-- README
-- Makefile

```

Details: Link to SRS_MOD_GUI

