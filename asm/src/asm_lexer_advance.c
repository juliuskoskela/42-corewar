#include "asm.h"

char	asm_lexer_peek(t_lexer *lexer)
{
	if (lexer->current_char == '\0')
		return (0);
	else
		return (lexer->input[lexer->current_pos + 1]);
}

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
