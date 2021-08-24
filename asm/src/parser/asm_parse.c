#include "asm.h"
#include "ast.h"
#include "parser.h"

void	asm_parse(t_astnode **tree, char *input)
{
	t_lexer		lexer;
	t_parser	parser;

	asm_init_lexer(&lexer, input);
	asm_init_parser(&parser, &lexer);
	*tree = asm_ast_program(&parser);
}
