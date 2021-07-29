#include "asm.h"

char	asm_lexer_peek(t_lexer *lexer)
{
	if (lexer->current_char == '\0')
		return (0);
	else
		return (lexer->input[lexer->current_pos + 1]);
}

