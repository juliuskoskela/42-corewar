#include "asm.h"
#include "ast.h"
#include "generate.h"
#include <stdlib.h>

static void	asm_set_default_param_sizes(int param_sizes[3],
t_astnode *parameter_list)
{
	t_astnode	*parameter;
	int			i;

	i = 0;
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (parameter->type == REGISTER)
			param_sizes[i] = REG_ADDR_SIZE;
		else if (parameter->type == INDIRECT)
			param_sizes[i] = IND_ADDR_SIZE;
		else
			param_sizes[i] = DIR_VAL_SIZE;
		parameter_list = parameter_list->right_child;
		i++;
	}
}

// lhs, rhs, dst
// ldi, lldi, and, or, xor
// ld?

static void	asm_promote_param_size(t_astnode *lhs, t_astnode *rhs,
int *lhs_size, int *rhs_size)
{
	int	lhs_type_size;
	int	rhs_type_size;

	lhs_type_size = *lhs_size;
	rhs_type_size = *rhs_size;
	if (lhs->type == REGISTER)
		lhs_type_size = REG_SIZE;
	if (rhs->type == REGISTER)
		rhs_type_size = REG_SIZE;
	if (lhs_type_size < rhs_type_size && lhs->type == DIRECT)
		*lhs_size = rhs_type_size;
	else if (rhs_type_size < lhs_type_size && rhs->type == DIRECT)
		*rhs_size = lhs_type_size;
}

void	asm_get_param_sizes(int param_sizes[3], t_astnode *instruction_node,
t_astnode *parameter_list)
{
	t_op		instruction;
	t_astnode	*lhs_param;
	t_astnode	*rhs_param;

	asm_set_default_param_sizes(param_sizes, parameter_list);
	asm_get_instruction(&instruction, instruction_node->value);
	if (s_cmp(instruction.mnemonic, "live") == 0)
		param_sizes[0] = 4;
	else if (s_cmp(instruction.mnemonic, "lldi") == 0
			// || s_cmp(instruction.mnemonic, "ldi") == 0
			|| s_cmp(instruction.mnemonic, "and") == 0
			|| s_cmp(instruction.mnemonic, "or") == 0
			|| s_cmp(instruction.mnemonic, "xor") == 0
			|| s_cmp(instruction.mnemonic, "ld") == 0)
	{
		lhs_param = parameter_list->left_child;
		rhs_param = parameter_list->right_child->left_child;
		asm_promote_param_size(lhs_param, rhs_param,
			&param_sizes[0], &param_sizes[1]);
	}
}
