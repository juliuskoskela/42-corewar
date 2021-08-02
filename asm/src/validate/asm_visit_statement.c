#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_statement(t_astnode *node, t_symbol_list *symbols,
t_header *header)
{
	int	ret;
	int	final_ret;

	ret = 1;
	final_ret = 1;
	if (node->left_child != NULL)
		ret = asm_visit_label(node->left_child, symbols);
	if (!ret)
		final_ret = 0;
	if (node->right_child != NULL && node->right_child->type == DIRECTIVE)
		ret = asm_visit_directive(node->right_child, header);
	else if (node->right_child != NULL
		&& node->right_child->type == INSTRUCTION)
		ret = asm_visit_instruction(node->right_child);
	if (!ret)
		final_ret = 0;
	return (final_ret);
}
