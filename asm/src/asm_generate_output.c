#include "asm.h"
#include "ast.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "core.h"
#include <ctype.h>

void	asm_generate_error(t_astnode *node, char *msg)
{
	print_fd(2, "Semantic error at [%zu, %zu]: %s %s\n",
		node->token.line_no,
		node->token.col,
		msg,
		node->value);
	exit(1);
}

void	asm_print_output_info(const char *str,
const char *param_type, int32_t value)
{
	if (param_type != NULL)
		print("%s %s %d : %#x\n", str, param_type, value, value);
	else
		print("%s %d : %#x\n", str, value, value);
}

void	asm_write_bytes(int8_t *program, uint32_t *lc, void *bytes, int n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		if (*lc == CHAMP_MAX_SIZE)
			asm_exit_error("Program too large");
		program[*lc] = ((int8_t *)bytes)[i];
		*lc = *lc + 1;
		i--;
	}
}

int	asm_add_label_to_list(t_symbol_list **labels, t_astnode *label)
{
	t_symbol_list	*node;

	if (*labels == NULL)
		*labels = asm_symbol_list_new(label, label->value);
	else
	{
		node = *labels;
		while (node->next != NULL)
			node = node->next;
		node->next = asm_symbol_list_new(label, label->value);
	}
	return (1);
}

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

void	asm_resolve_label_forward_refs(int8_t *program, t_symbol_list *label)
{
	t_refnode	*ref_node;
	t_refnode	*next;
	int32_t		value;

	ref_node = label->forward_refs;
	while (ref_node != NULL)
	{
		value = label->node->num_value - (int32_t)ref_node->op_location;
		if (ASM_PRINT_DEBUG)
			asm_print_output_info("resolve forward reference for label",
				label->symbol, value);
		asm_write_bytes(program, &ref_node->ref_location, &value, 2);
		next = ref_node->next;
		free(ref_node);
		ref_node = next;
	}
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

void	asm_write_argument_coding_byte(int8_t *program, uint32_t *lc,
t_astnode *parameter_list)
{
	t_astnode	*parameter;
	uint8_t		acb;
	uint8_t		i;

	acb = 0;
	i = 6;
	if (ASM_PRINT_DEBUG)
		print("arguments: ");
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (ASM_PRINT_DEBUG)
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
	if (ASM_PRINT_DEBUG)
		asm_print_output_info("\n=> write argument coding byte", NULL, acb);
	asm_write_bytes(program, lc, &acb, 1);
}

void	asm_save_label_address(t_output_data *data, uint32_t lc,
t_symbol_list **labels)
{
	t_symbol_list	*label;

	while (*labels != NULL)
	{
		label = asm_symbol_list_lookup(&data->symbols, (*labels)->symbol);
		if (ASM_PRINT_DEBUG)
			asm_print_output_info("save address for label",
				label->symbol, (int32_t)lc);
		label->node->num_value = (int32_t)lc;
		asm_resolve_label_forward_refs(data->program, label);
		asm_symbol_list_delete(labels, (*labels)->symbol);
	}
}

int	asm_generate_instruction(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_op		instruction;
	uint32_t	current_op_lc;

	if (ASM_PRINT_DEBUG)
		asm_print_output_info("\nGenerate instruction",
			node->value, (int32_t)(*lc));
	current_op_lc = *lc;
	if (*labels != NULL)
		asm_save_label_address(data, current_op_lc, labels);
	asm_get_instruction(&instruction, node->value);
	if (ASM_PRINT_DEBUG)
		asm_print_output_info("write opcode", NULL, instruction.opcode);
	asm_write_bytes(data->program, lc, &instruction.opcode, 1);
	if (instruction.has_argument_coding_byte)
		asm_write_argument_coding_byte(data->program, lc, node->right_child);
	else if (ASM_PRINT_DEBUG)
		print("no argument coding byte\n");
	asm_write_arguments(data->program, lc, current_op_lc,
		&data->symbols, node->right_child);
	return (1);
}

int	asm_generate_statement(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	if (node->left_child != NULL)
		asm_add_label_to_list(labels, node->left_child);
	if (node->right_child != NULL && node->right_child->type == INSTRUCTION)
		return (asm_generate_instruction(data, lc, labels, node->right_child));
	return (1);
}

int	asm_generate_bytecode_program(t_output_data *data, t_astnode *tree)
{
	uint32_t		location_counter;
	t_symbol_list	*defined_labels;
	t_astnode		*statement_list;

	location_counter = 0;
	defined_labels = NULL;
	statement_list = tree->right_child;
	while (statement_list != NULL)
	{
		if (!asm_generate_statement(data, &location_counter,
				&defined_labels, statement_list->left_child))
			return (0);
		statement_list = statement_list->right_child;
	}
	data->header.prog_size = location_counter;
	if (ASM_PRINT_DEBUG)
		asm_print_symbol_list(&data->symbols,
			"\n\nSymbol table after second pass through AST:");
	return (1);
}

int	asm_generate_output(t_output_data *data, t_astnode *tree)
{
	int	ret;

	ret = asm_generate_bytecode_program(data, tree);
	if (!ret)
		return (0);
	return (1);
}
