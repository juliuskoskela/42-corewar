#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_instruction(t_astnode *node)
{
	t_op	instruction;

	if (!asm_get_instruction(&instruction, node->value))
		return (asm_semantic_error(node, "Invalid opcode"));
	return (asm_visit_parameter_list(node->right_child, 1, instruction));
}
