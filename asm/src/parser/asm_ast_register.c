#include "asm.h"
#include "ast.h"
#include "parser.h"

t_astnode	*asm_ast_register(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(REGISTER,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	return (node);
}
