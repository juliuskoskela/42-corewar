#include "asm.h"
#include "parser.h"
#include <stdlib.h>

void	asm_consume_token(t_parser *parser, t_token_type expected_type,
int free_token_value)
{
	if (parser->current_token.type == expected_type)
	{
		if (free_token_value)
			free(parser->current_token.value);
		parser->current_token = asm_get_next_token(parser->lexer);
	}
	else
		asm_parser_error(parser, expected_type);
}
