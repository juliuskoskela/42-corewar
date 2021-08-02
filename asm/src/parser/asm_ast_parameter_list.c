#include "asm.h"
#include "ast.h"
#include "parser.h"

static t_astnode	*asm_ast_parameter(t_parser *parser)
{
	if (parser->current_token.type == DIRECT_TOKEN)
		return (asm_ast_direct(parser));
	else if (parser->current_token.type == INTEGER_TOKEN
		|| parser->current_token.type == LABEL_TOKEN)
		return (asm_ast_indirect(parser));
	else
		return (asm_ast_register(parser));
}

t_astnode	*asm_ast_parameter_list(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(PARAMETER_LIST, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	node->left_child = asm_ast_parameter(parser);
	if (parser->current_token.type == SEPARATOR_TOKEN)
	{
		asm_consume_token(parser, SEPARATOR_TOKEN, 1);
		node->right_child = asm_ast_parameter_list(parser);
	}
	return (node);
}
