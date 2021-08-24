#include "asm.h"
#include "ast.h"
#include "parser.h"

t_astnode	*asm_ast_instruction(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(INSTRUCTION,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	node->right_child = asm_ast_parameter_list(parser);
	return (node);
}
