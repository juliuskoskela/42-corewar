#include "asm.h"

void	asm_init_parser(t_parser *parser, t_lexer *lexer)
{
	parser->lexer = lexer;
	parser->current_token = asm_get_next_token(lexer);
	parser->error_occurred = 0;
}

