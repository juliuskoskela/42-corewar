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

static void	asm_write_direct(t_output_data *data, uint32_t *lc,
uint32_t curr_op_lc, t_astnode *parameter, int size)
{
	if (parameter->type == INTEGER)
		asm_get_numeric_value(&parameter->num_value, parameter->value);
	else
		asm_get_label_value(data, lc, curr_op_lc, parameter, size);
	if (data->verbose)
	{
		asm_print_output_info("write direct", g_astnode_types[parameter->type],
			parameter->num_value);
	}
	asm_write_bytes(data, lc, &parameter->num_value, size);
}

static void	asm_write_indirect(t_output_data *data, uint32_t *lc,
uint32_t curr_op_lc, t_astnode *parameter, int size)
{
	if (parameter->type == INTEGER)
		asm_get_numeric_value(&parameter->num_value, parameter->value);
	else
		asm_get_label_value(data, lc, curr_op_lc, parameter, size);
	if (data->verbose)
	{
		asm_print_output_info("write indirect",
			g_astnode_types[parameter->type], parameter->num_value);
	}
	asm_write_bytes(data, lc, &parameter->num_value, size);
}

static void	asm_write_register(t_output_data *data, uint32_t *lc,
t_astnode *parameter, int size)
{
	char	*reg;

	reg = parameter->value;
	reg++;
	if (!asm_get_numeric_value(&parameter->num_value, reg))
		asm_generate_error(parameter, "Invalid register");
	if (data->verbose)
		asm_print_output_info("write register", NULL, parameter->num_value);
	asm_write_bytes(data, lc, &parameter->num_value, size);
}

void	asm_write_arguments(t_output_data *data, uint32_t *lc,
uint32_t curr_op_lc, t_astnode *instruction_node)
{
	t_astnode	*parameter_list;
	t_astnode	*parameter;
	int			param_sizes[3];
	int			i;

	parameter_list = instruction_node->right_child;
	asm_get_param_sizes(param_sizes, instruction_node, parameter_list);
	i = 0;
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (parameter->type == REGISTER)
			asm_write_register(data, lc, parameter, param_sizes[i]);
		else if (parameter->type == INDIRECT)
			asm_write_indirect(data, lc, curr_op_lc, parameter->right_child, param_sizes[i]);
		else
			asm_write_direct(data, lc, curr_op_lc, parameter->right_child, param_sizes[i]);
		parameter_list = parameter_list->right_child;
		i++;
	}
}
