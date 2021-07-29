#include "asm.h"
#include <ctype.h>

t_token_type	asm_peek_next_token(t_lexer *lexer)
{
	if (lexer->current_char == '\0')
		return (EOF_TOKEN);
	else if (lexer->current_char == '.')
		return (DOT_TOKEN);
	else if (lexer->current_char == '"')
		return (STRING_TOKEN);
	else if (lexer->current_char == COMMENT_CHAR
			|| lexer->current_char == COMMENT_SEMICOLON)
		return (COMMENT_TOKEN);
	else if (lexer->current_char == SEPARATOR_CHAR)
		return (SEPARATOR_TOKEN);
	else if (lexer->current_char == DIRECT_CHAR)
		return (DIRECT_TOKEN);
	else if (lexer->current_char == LABEL_CHAR)
		return (LABEL_TOKEN);
	else if (isdigit(lexer->current_char) || lexer->current_char == '-')
		return (INTEGER_TOKEN);
	else if (isalpha(lexer->current_char))
		return (ID_TOKEN);
	else
		return (ERROR_TOKEN);
}
