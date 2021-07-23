#include "asm.h"

t_parser	asm_init_parser(t_lexer *lexer)
{
	t_parser	parser;

	parser.lexer = lexer;
	parser.current_token = asm_get_next_token(lexer);
	parser.error_occurred = 0;
	return (parser);
}
