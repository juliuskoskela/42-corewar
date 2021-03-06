#include "asm.h"
#include "ast.h"
#include "parser.h"

t_astnode	*asm_ast_direct(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(DIRECT, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	asm_consume_token(parser, DIRECT_TOKEN, 1);
	if (parser->current_token.type == INTEGER_TOKEN)
	{
		node->right_child = asm_astnode_new(INTEGER,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, INTEGER_TOKEN, 0);
	}
	else
	{
		asm_consume_token(parser, LABEL_TOKEN, 1);
		node->right_child = asm_astnode_new(LABEL,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, ID_TOKEN, 0);
	}
	return (node);
}
