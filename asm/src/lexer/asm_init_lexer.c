#include "asm.h"

void	asm_init_lexer(t_lexer *lexer, const char *input)
{
	lexer->input = input;
	lexer->current_pos = 0;
	lexer->current_char = input[0];
	lexer->line_no = 1;
	lexer->col = 1;
}
