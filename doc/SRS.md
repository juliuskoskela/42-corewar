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
---- corewar
------ inc
------ src
------ README
------ Makefile
---- graphics
------ inc
------ src
------ assets
------ README
------ Makefile
-- doc
-- pic
-- Makefile
-- README
-- author

```

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

### Corewar Module

Module for creating the virtual machine environment for the champion arena.

Target: corewar
namespace: war_

```

corewar
-- inc
-- src
-- README
-- Makefile

```

Details: Link to SRS_MOD_COREWAR

### Graphics Module

To be decided...
