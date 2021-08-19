#include "asm.h"

t_token	asm_get_eof_token(t_lexer *lexer)
{
	t_token	token;

	token = asm_init_token(EOF_TOKEN, NULL, lexer->line_no, lexer->col);
	return (token);
}
