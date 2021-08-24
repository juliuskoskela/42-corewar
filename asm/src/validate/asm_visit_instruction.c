#include "asm.h"
#include "ast.h"
#include "validate.h"

void	asm_visit_instruction(t_astnode *node)
{
	t_op	instruction;
	int		params;

	if (!asm_get_instruction(&instruction, node->value))
		asm_semantic_error(node, "Invalid opcode");
	params = asm_visit_parameter_list(node->right_child, 1, instruction);
	if (params != (int)instruction.param_count)
		asm_semantic_error(node, "Invalid amount of arguments for instruction");
}
