#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_statement_list(t_astnode *node, t_symbol_list *symbols,
t_header *header)
{
	int	ret;
	int	final_ret;

	ret = 1;
	final_ret = 1;
	if (node->left_child != NULL)
		ret = asm_visit_statement(node->left_child, symbols, header);
	if (!ret)
		final_ret = 0;
	if (node->right_child != NULL)
		ret = asm_visit_statement_list(node->right_child, symbols, header);
	if (!ret)
		final_ret = 0;
	return (final_ret);
}
