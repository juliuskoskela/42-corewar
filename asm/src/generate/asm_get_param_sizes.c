/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	asm_get_param_sizes(int param_sizes[3], t_astnode *instruction_node,
t_astnode *parameter_list)
{
	t_op		instruction;

	asm_set_default_param_sizes(param_sizes, parameter_list);
	asm_get_instruction(&instruction, instruction_node->value);
	if (s_cmp(instruction.mnemonic, "live") == 0)
		param_sizes[0] = 4;
	else if (s_cmp(instruction.mnemonic, "lldi") == 0
		|| s_cmp(instruction.mnemonic, "and") == 0
		|| s_cmp(instruction.mnemonic, "or") == 0
		|| s_cmp(instruction.mnemonic, "xor") == 0
		|| s_cmp(instruction.mnemonic, "ld") == 0)
	{
		if (parameter_list->left_child->type == DIRECT)
			param_sizes[0] = REG_SIZE;
		if (parameter_list->right_child->left_child->type == DIRECT)
			param_sizes[1] = REG_SIZE;
	}
}
