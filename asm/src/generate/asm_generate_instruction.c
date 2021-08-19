#include "asm.h"
#include "ast.h"
#include "generate.h"

static void	asm_write_argument_coding_byte(t_output_data *data, uint32_t *lc,
t_astnode *parameter_list)
{
	t_astnode	*parameter;
	uint8_t		acb;
	uint8_t		i;

	acb = 0;
	i = 6;
	if (data->verbose)
		print("arguments: ");
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (data->verbose)
			print("%s ", g_astnode_types[parameter->type]);
		if (parameter->type == REGISTER)
			acb = (uint8_t)(acb | (REG_CODE << i));
		else if (parameter->type == DIRECT)
			acb = (uint8_t)(acb | (DIR_CODE << i));
		else if (parameter->type == INDIRECT)
			acb = (uint8_t)(acb | (IND_CODE << i));
		i -= 2;
		parameter_list = parameter_list->right_child;
	}
	if (data->verbose)
		asm_print_output_info("\n=> write argument coding byte", NULL, acb);
	asm_write_bytes(data, lc, &acb, 1);
}

static void	asm_resolve_label_forward_refs(t_output_data *data,
t_symbol_list *label)
{
	t_refnode	*ref_node;
	t_refnode	*next;
	int32_t		value;

	ref_node = label->forward_refs;
	while (ref_node != NULL)
	{
		value = label->node->num_value - (int32_t)ref_node->op_location;
		if (data->verbose)
			asm_print_output_info("resolve forward reference for label",
				label->symbol, value);
		asm_write_bytes(data, &ref_node->ref_location, &value,
			ref_node->size);
		next = ref_node->next;
		free(ref_node);
		ref_node = next;
	}
}

static void	asm_save_label_address(t_output_data *data, uint32_t lc,
t_symbol_list **labels)
{
	t_symbol_list	*label;

	while (*labels != NULL)
	{
		label = asm_symbol_list_lookup(&data->symbols, (*labels)->symbol);
		if (data->verbose)
			asm_print_output_info("save address for label",
				label->symbol, (int32_t)lc);
		label->node->num_value = (int32_t)lc;
		asm_resolve_label_forward_refs(data, label);
		asm_symbol_list_delete(labels, (*labels)->symbol);
	}
}

int	asm_generate_instruction(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_op		instruction;
	uint32_t	current_op_lc;

	if (data->verbose)
		asm_print_output_info("\nGenerate instruction",
			node->value, (int32_t)(*lc));
	current_op_lc = *lc;
	if (*labels != NULL)
		asm_save_label_address(data, current_op_lc, labels);
	asm_get_instruction(&instruction, node->value);
	if (data->verbose)
		asm_print_output_info("write opcode", NULL, instruction.opcode);
	asm_write_bytes(data, lc, &instruction.opcode, 1);
	if (instruction.has_argument_coding_byte)
		asm_write_argument_coding_byte(data, lc, node->right_child);
	else if (data->verbose)
		print("no argument coding byte\n");
	asm_write_arguments(data, lc, current_op_lc, node->right_child);
	return (1);
}
