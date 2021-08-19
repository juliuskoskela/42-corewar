#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_program(t_astnode *node, t_symbol_list *symbols, t_header *header)
{
	int	ret;

	ret = 1;
	if (node->right_child != NULL)
		ret = asm_visit_statement_list(node->right_child, symbols, header);
	if (header->prog_name[0] == '\0')
	{
		asm_semantic_error(node, "Missing .name directive");
		return (0);
	}
	else if (header->comment[0] == '\0')
	{
		asm_semantic_error(node, "Missing .comment directive");
		return (0);
	}
	return (ret);
}
