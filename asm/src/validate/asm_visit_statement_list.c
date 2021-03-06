#include "asm.h"
#include "ast.h"
#include "validate.h"

void	asm_visit_statement_list(t_astnode *node, t_symbol_list *symbols,
t_header *header)
{
	if (node->left_child != NULL)
		asm_visit_statement(node->left_child, symbols, header);
	if (node->right_child != NULL)
		asm_visit_statement_list(node->right_child, symbols, header);
}
