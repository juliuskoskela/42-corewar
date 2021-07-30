#include "asm.h"
#include "ast.h"
#include "parser.h"

t_astnode	*asm_ast_program(t_parser *parser)
{
	t_astnode	*program_node;

	program_node = asm_astnode_new(PROGRAM, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	program_node->right_child = asm_ast_statement_list(parser);
	return (program_node);
}
