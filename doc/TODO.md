# TO DO

Before submitting:
- author file
- Somerme
- Makefile rules
## VM

- check leaks
- check modulos: `All the addresses are related to PC and to IDX_MOD except for lld, lldi and
lfork`
- check zf: 1) is implemented where appropriate, 2) check is made against the correct value. This needs to be added to ld, ldi, lld and lldi instructions.

(- hard coded argument lengths in instruction function variables -> let that be)

### Instructions

| Function | Implemented | Tested |
|----------|-------------|--------|
|  `live`  |    [Yes]     |  [Some]  |
|  `ld`    |    [Yes]    |  [Some]  |
|  `lld`   |    [Yes]    |  [Some]  |
|  `ldi`   |    [Yes]     |  [Some]  |
|  `lldi`  |    [Yes]     |  [Some]  |
|  `st`    |    [Yes]    |  [Some]  |
|  `sti`   |    [Yes]    |  [Some]  |
|  `add`   |    [Yes]    |  [Some]  |
|  `sub`   |    [Yes]    |  [Some]  |
|  `and`   |    [Yes]    |  [Some]  |
|  `or`    |    [Yes]    |  [Some]  |
|  `xor`   |    [Yes]    |  [Some]  |
|  `zjmp`  |    [Yes]     |  [Some]  |
|  `fork`  |    [Yes]    |  [Some]  |
|  `lfork` |    [Yes]    |  [Some]  |
|  `aff`   |    [Yes]     |  [Yes]  |

### To do for each instruction

1. Check the definition & requirements for instruction from subject & docs
2. Add those requirements as a comment
3. First implementation
4. Add descriptive prints for debugging purposes and set them behind a verbosity flag
5. Write a test player that tests all combinations of arguments

### Tests

- unit tests for each instruction
- tests with single players: more complex combinations of instructions
- tests with multiple players
- tests for other required (+ bonus) features

### Player

- create our own player that wins

## ASM

- check leaks
- check github issues