## ASM: Assembler for champions

```
./asm mychampion.s
```

- reads the assembly code from the file with a suffix ``.s`` given as argument, parses it into a bytecode format that it then writes to a file with the same name as the argument but with the suffix ``.cor``
- in case of error, writes an error message to stderr

In essence, the asm program constitutes a simple compiler.

A basic compiler is made up of the following components:

1) Lexer / scanner
   - reads the input file character by character to produce tokens
2) Parser
   - parses the input into an abstract syntax tree (AST) according to a specified grammar
   - according to the grammar rules, requests tokens from the lexer and checks that their ordering is in line with the rules => syntax analysis
3) Semantic analyzer
   - traverses the abstract syntax tree and makes some static semantic checks, e.g. whether
     - an instruction exists
     - number of operands/parameters is correct for a given instruction
     - operands/parameters are of correct type
     - register exists
     - label is declared
     - literal values have correct size
4) Code emitter (?)
   - traverses the abstract syntax tree and outputs the bytecode representation in the output file

If any errors are detected during the lexing, parsing or semantic analysis, nothing is written to the output file, and a meaninful error message should be displayed, showing the type and location of the error in the source file.

Therefore, a grammar and some lexing rules for defining tokens are needed. An example following [the EBNF notation](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form), inspired by [this post about parsing RISC-V assembly](https://web.eecs.utk.edu/~azh/blog/parsingriscv.html), would be

```
# Grammar
program			= { [ label ] [ directive | instruction ] [ comment ] newline }
label			= label_name LABEL_CHAR
directive		= '.' command_string string
command_string	= NAME_CMD_STRING
				| COMMENT_CMD_STRING
instruction 	= symbol [ parameter { SEPARATOR_CHAR parameter } ]
parameter		= register
				| direct
				| indirect
register		= 'r' number
direct			= DIRECT_CHAR ( number | LABEL_CHAR label_name )
indirect		= number
				| LABEL_CHAR label_name

# Lexer rules (expressed with regular expressions for brevity)
newline			= [\n\r]+
comment			= #[^\n\r]+
label_name		= [LABEL_CHARS]+
string			= \"([^\n\r"])+\"
symbol			= [a-zA-Z][a-zA-Z0-9_]*
number			= -?[0-9]+

# In addition, any whitespace is skipped and considered token delimiters
```
