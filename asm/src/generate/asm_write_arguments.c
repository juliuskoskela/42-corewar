#include "asm.h"
#include "ast.h"
#include "generate.h"
#include <stdlib.h>

void	asm_add_forward_reference_to_label(t_symbol_list *label,
uint32_t ref_location, uint32_t op_location)
{
	t_refnode	*new_node;
	t_refnode	*node;

	new_node = (t_refnode *)malloc(sizeof(t_refnode));
	if (new_node == NULL)
		asm_exit_error("Malloc error in allocating ref node");
	new_node->op_location = op_location;
	new_node->ref_location = ref_location;
	new_node->next = NULL;
	if (label->forward_refs == NULL)
		label->forward_refs = new_node;
	else
	{
		node = label->forward_refs;
		while (node->next != NULL)
			node = node->next;
		node->next = new_node;
	}
}

void	asm_write_direct(int8_t *program, uint32_t *lc,
uint32_t current_op_lc, t_symbol_list *symbols, t_astnode *parameter)
{
	t_symbol_list	*label;

	if (parameter->type == INTEGER)
		asm_get_numeric_value(&parameter->num_value, parameter->value);
	else
	{
		label = asm_symbol_list_lookup(symbols, parameter->value);
		if (label == NULL)
			asm_generate_error(parameter, "Undefined label");
		if (label->node->num_value != 0)
		{
			parameter->num_value = label->node->num_value - (int32_t)current_op_lc;
		}
		else
		{
			if (ASM_PRINT_DEBUG)
				asm_print_output_info("add forward reference for label",
					label->symbol, parameter->num_value);
			asm_add_forward_reference_to_label(label, *lc, current_op_lc);
		}
	}
	if (ASM_PRINT_DEBUG)
		asm_print_output_info("write direct", g_astnode_types[parameter->type],
			parameter->num_value);
	asm_write_bytes(program, lc, &parameter->num_value, 2);
}

void	asm_write_indirect(int8_t *program, uint32_t *lc,
uint32_t current_op_lc, t_symbol_list *symbols, t_astnode *parameter)
{
	t_symbol_list	*label;

	if (parameter->type == INTEGER)
		asm_get_numeric_value(&parameter->num_value, parameter->value);
	else
	{
		label = asm_symbol_list_lookup(symbols, parameter->value);
		if (label == NULL)
			asm_generate_error(parameter, "Undefined label");
		if (label->node->num_value != 0)
		{
			parameter->num_value = label->node->num_value - (int32_t)current_op_lc;
		}
		else
		{
			if (ASM_PRINT_DEBUG)
				asm_print_output_info("add forward reference for label",
					label->symbol, parameter->num_value);
			asm_add_forward_reference_to_label(label, *lc, current_op_lc);
		}
	}
	if (ASM_PRINT_DEBUG)
		asm_print_output_info("write indirect",
			g_astnode_types[parameter->type], parameter->num_value);
	asm_write_bytes(program, lc, &parameter->num_value, 2);
}

void	asm_write_register(int8_t *program, uint32_t *lc, t_astnode *parameter)
{
	char	*value;

	value = parameter->value;
	if (*value != 'r')
		asm_generate_error(parameter, "Invalid register");
	value++;
	if (!asm_get_numeric_value(&parameter->num_value, value))
		asm_generate_error(parameter, "Invalid register");
	if (parameter->num_value < 1 || parameter->num_value > REG_NUMBER)
		asm_generate_error(parameter, "Invalid register");
	if (ASM_PRINT_DEBUG)
		asm_print_output_info("write register", NULL, parameter->num_value);
	asm_write_bytes(program, lc, &parameter->num_value, 1);
}

void	asm_write_arguments(int8_t *program, uint32_t *lc,
uint32_t current_op_lc, t_symbol_list *symbols, t_astnode *parameter_list)
{
	t_astnode	*parameter;

	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (parameter->type == REGISTER)
		{
			asm_write_register(program, lc, parameter);
		}
		else if (parameter->type == INDIRECT)
		{
			asm_write_indirect(program, lc, current_op_lc,
				symbols, parameter->right_child);
		}
		else
		{
			asm_write_direct(program, lc, current_op_lc,
				symbols, parameter->right_child);
		}
		parameter_list = parameter_list->right_child;
	}
}
