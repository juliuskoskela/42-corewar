#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_parameter_list(t_astnode *node, uint32_t param_nbr,
t_op instruction)
{
	int	ret;

	if (param_nbr > instruction.param_count)
		return (asm_semantic_error(node, "Too many arguments for instruction"));
	ret = asm_visit_parameter(node->left_child, param_nbr, instruction);
	if (ret == 1 && node->right_child != NULL)
	{
		ret = asm_visit_parameter_list(node->right_child,
				param_nbr + 1, instruction);
	}
	return (ret);
}
