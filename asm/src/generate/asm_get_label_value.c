#include "asm.h"
#include "ast.h"
#include "generate.h"
#include <stdlib.h>

static void	asm_add_forward_ref_to_label(t_symbol_list *label,
uint32_t ref_location, uint32_t op_location, size_t size)
{
	t_refnode	*new_node;
	t_refnode	*node;

	new_node = (t_refnode *)malloc(sizeof(t_refnode));
	if (new_node == NULL)
		asm_exit_error("Malloc error in allocating ref node");
	new_node->op_location = op_location;
	new_node->ref_location = ref_location;
	new_node->size = size;
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

void	asm_get_label_value(t_output_data *data, uint32_t *lc,
uint32_t curr_op_lc, t_astnode *parameter, int size)
{
	t_symbol_list	*label;

	label = asm_symbol_list_lookup(&data->symbols, parameter->value);
	if (label == NULL)
		asm_generate_error(parameter, "Undefined label");
	if (label->node->num_value != 0)
		parameter->num_value = label->node->num_value - (int32_t)curr_op_lc;
	else
	{
		if (data->verbose)
		{
			asm_print_output_info("add forward reference for label",
				label->symbol, parameter->num_value);
		}
		asm_add_forward_ref_to_label(label, *lc, curr_op_lc, size);
	}
}
