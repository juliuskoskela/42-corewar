#include "asm.h"

t_lexer	asm_init_lexer(const char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.current_pos = 0;
	lexer.current_char = input[0];
	lexer.line_no = 1;
	lexer.col = 1;
	return (lexer);
}