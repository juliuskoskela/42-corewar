## ASM: Assembler for champions

```
./asm mychampion.s
```

- reads the assembly code from the file with a suffix ``.s`` given as argument, parses it into a bytecode format that it then writes to a file with the same name as the argument but with the suffix ``.cor``
- in case of error, writes an error message to stderr

In essence, the asm program constitutes a simple compiler / assembler.

Our assembler is currently made up of the following components:

1) Lexer / scanner (asm_get_next_token)
   - reads the input file character by character to produce tokens
2) Parser (asm_parse)
   - parses the input into an abstract syntax tree (AST) according to a specified grammar
   - according to the grammar rules, requests tokens from the lexer and checks that their ordering is in line with the rules => syntax analysis
3) Semantic analysis: first pass of the AST (asm_validate)
   - traverses the abstract syntax tree and makes some static semantic checks, e.g. whether
     - given directive exists and is not duplicate
     - given instruction exists and
       - number of operands/parameters is correct
       - operands/parameters are of correct type
       - register exists (not yet)
       - literal values have correct size (not yet)
   - saves all label definitions to a symbol table
4) Code generation (asm_generate_output)
   - traverses the abstract syntax tree and generates the bytecode representation
     - see bytecode format for instruction statements below
     - name resolution for labels (not yet)
   - writes header contents and program to output file

- at which point should string values of parameters be converted to the integer values?

If any errors are detected during the lexing, parsing or semantic analysis, nothing is written to the output file, and a meaninful error message should be displayed, showing the type and location of the error in the source file.

# Grammar and lexing rules

Therefore, a grammar and some lexing rules for defining tokens are needed. An example following [the EBNF notation](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form), inspired by [this post about parsing RISC-V assembly](https://web.eecs.utk.edu/~azh/blog/parsingriscv.html), would be

```
# Grammar
program			= statement_list
statement_list  = statement [ statement_list ]
statement       = { [ label ] [ directive | instruction ] [ comment ] newline }
label			= id LABEL_CHAR
directive		= '.' id [ string ]
instruction 	= id [ parameter { SEPARATOR_CHAR parameter } ]
parameter		= register
				| direct
				| indirect
register		= id
direct			= DIRECT_CHAR ( number | LABEL_CHAR id )
indirect		= integer
				| LABEL_CHAR id

# Lexer rules (expressed with regular expressions for brevity)
newline			= [\n\r]+
comment			= #[^\n\r]+
label_name		= [LABEL_CHARS]+
string			= \"([^\n\r"])+\"
id	      		= [a-zA-Z][a-zA-Z0-9_]*
number			= -?[0-9]+ | 0x[0-9a-f]+

# In addition, any whitespace is skipped and considered token delimiters
```

# Code generation: bytecode format

Output file will be in a "bytecode" format.

Output file starts with the contents of the header that is defined as
```c
typedef struct header_s
{
   unsigned int   magic;
   char           prog_name[PROG_NAME_LENGTH + 1];
   unsigned int   prog_size;
   char           comment[COMMENT_LENGTH + 1];
}                 header_t;
```
Therefore, the first 4 bytes contain the magic number, next PROG_NAME_LENGTH bytes the program name from the ``.name`` directive, next 4 bytes the program size and finally next COMMENT_LENGTH bytes the comment from the ``.comment`` directive.

An example snippet from the beginning of the hex dump of ``42.cor``:
```hex
  Offset: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 	
00000000: 00 EA 83 F3 34 32 00 00 00 00 00 00 00 00 00 00    .j.s42..........
00000010: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000060: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
00000080: 00 00 00 00 00 00 00 00 00 00 03 E1 4A 75 73 74    ...........aJust
00000090: 20 61 20 62 61 73 69 63 20 57 69 6E 6E 65 72 20    .a.basic.Winner.
000000a0: 50 72 6F 67 72 61 6D 00 00 00 00 00 00 00 00 00    Program.........
```

After the header contents, the instructions of the program itself will be written sequentially. Each instruction will be in the following format:
```
opcode [ argument coding byte ] arguments
```
The argument coding byte is used to specify the types of the arguments that follow so that they can be read and interpreted correctly. According to the header ``op.h`` provided with the project subject, he binary encoding is ``01`` for a register, ``10`` for a direct and ``11`` for an indirect parameter. Some of the opcodes that only take one parameter of a specific type do not have an argument coding byte.

For example, the arguments ``r2, 23, %34`` give the coding byte ``01111000`` in binary (``01`` for register, ``11`` for indirect, ``10`` for direct, and last two bits unused) that becomes ``0x78`` in hexadecimal.

Here is an example program from the subject:
```s
.name "zork"
.comment "just a basic living prog"

l2:     sti r1,%:live,%1
        and r1,%0,r1
live:   live %1
        zjmp %:live
```
And the corresponding bytes for the four instructions written as hexadecimals (header content omitted):
```
0x0b,0x68,0x01,0x00,0x0f,0x00,0x01
0x06,0x64,0x01,0x00,0x00,0x00,0x00,0x01
0x01,0x00,0x00,0x00,0x01
0x09,0xff,0xfb
```
And the corresponding hex dump
```
00000890: 0B 68 01 00 0F 00 01 06 64 01 00 00 00 00 01 01    .h......d.......
000008a0: 00 00 00 01 09 FF FB                               ......{
```
Breaking them down, row by row:
- ``l2:     sti r1, %:live, %1`` => ``0x0b,0x68,0x01,0x00,0x0f,0x00,0x01``
  - the mnemonic ``sti`` corresponds to opcode 11 which is ``0x0b`` in hex
  - ``sti`` takes three parameters (register, register/direct/indirect, register/direct) so it is followed by an argument coding byte. Here, the arguments are a register, a direct and a direct, producing the byte ``01101000`` that corresponds to the hexadecimal byte ``0x68``.
  - Next, ``r1`` is represented by ``0x01``, ``%:live`` by ``0x00,0x0f`` (value of label ``:live`` denotes the offset from current instrucion's address to the address of the instruction whose label ``:live`` is, and here the offset is 15), and ``%1`` by ``0x00,0x01``.


- ``        and r1,%0,r1`` => ``0x06,0x64,0x01,0x00,0x00,0x00,0x00,0x01``
  - the mnemonic ``and`` corresponds to opcode 6 => ``0x06``
  - takes three parameters (register/direct/indirect, register/direct/indirect, register) so it has an argument coding byte. Here, arguments are a register, a direct, and a register, so the coding byte becomes ``01100100`` => ``0x64``.
  - ``r1`` corresponds to ``0x01``, ``%0``  to ``0x00,0x00,0x00,0x00`` and ``r1`` to ``0x01``


- ``live:   live %1`` => ``0x01,0x00,0x00,0x00,0x01``
  - the mnemonic ``live``corresponds to opcode 1 => ``0x01``
  - takes one parameter, a 4-byte direct, and no argument coding byte. therefore, the opcode byte is directly followed by the argument ``%1`` that corresponds to ``0x00,0x00,0x00,0x01``.


- ``zjmp %:live`` => ``0x09,0xff,0xfb``
  - the mnemonic ``zjmp`` corresponds to opcode 9 => ``0x09``
  - takes one parameter, a direct, and no argument coding byte. ``%:live`` corresponds to ``0xff,0xfb`` which appears to be -5 (big endian int16), again the offset from current instruction's address to the instruction denoted by ``:live``.


- questions:
  - why do direct values sometimes take 2 bytes and sometimes 4 bytes?
  - how are label offsets counted?
