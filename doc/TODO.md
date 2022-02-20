# TO DO

## VM

- check norme
- check leaks
- check modulos: `All the addresses are related to PC and to IDX_MOD except for lld, lldi and
lfork`
- check zf: 1) is implemented where appropriate, 2) check is made against the correct value
- hard coded argument lengths in instruction function variables
- place all debug prints behind appropriate verbosity level flags (+ coloured prints behind coloured flag)

### Instructions

| Function | Implemented | Tested |
|----------|-------------|--------|
|  `live`  |    [Yes]     |  [No]  |
|  `ld`    |    [Yes]    |  [Some]  |
|  `lld`   |    [Yes]    |  [No]  |
|  `ldi`   |    [Yes]     |  [No]  |
|  `lldi`  |    [Yes]     |  [No]  |
|  `st`    |    [Yes]    |  [Some]  |
|  `sti`   |    [Yes]    |  [Some]  |
|  `add`   |    [Yes]    |  [No]  |
|  `sub`   |    [Yes]    |  [No]  |
|  `and`   |    [Yes]    |  [Some]  |
|  `or`    |    [Yes]    |  [Some]  |
|  `xor`   |    [Yes]    |  [Some]  |
|  `zjmp`  |    [Yes]     |  [No]  |
|  `fork`  |    [Yes]    |  [No]  |
|  `lfork` |    [Yes]    |  [No]  |
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

- check norme
- check leaks
- check github issues