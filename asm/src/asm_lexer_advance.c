#include "asm.h"

void	asm_lexer_advance(t_lexer *lexer)
{
	lexer->current_pos++;
	lexer->current_char = lexer->input[lexer->current_pos];
	if (lexer->current_char == '\n' || lexer->current_char == '\r')
	{
		lexer->file_row++;
		lexer->file_col = 1;
	}
	else
		lexer->file_col++;
}
