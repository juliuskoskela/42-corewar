#include "asm.h"
#include "ast.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

int	get_instruction(t_op *dst, char *mnemonic)
{
	size_t	i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (strcmp(mnemonic, g_op_tab[i].mnemonic) == 0)
		{
			*dst = g_op_tab[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_numeric_value(int32_t *dst, char *str)
{
	static const char	digits[17] = "0123456789abcdef";
	int32_t				base;
	int32_t				value;
	int32_t				sign;
	int32_t				i;

	value = 0;
	sign = 1;
	if (strncmp(str, "0x", 2) == 0)
	{
		base = 16;
		str += 2;
	}
	else
	{
		base = 10;
		if (*str == '-')
		{
			sign = -1;
			str++;
		}
	}
	while (isdigit(*str) || (*str >= 'a' && *str <= 'f'))
	{
		i = 0;
		while (digits[i] != *str)
			i++;
		value = value * base + i;
		str++;
	}
	if (*str != '\0')
		return (0);
	*dst = sign * value;
	return (1);
}

void	write_bytes(int8_t *program, uint32_t *lc, void *bytes, int n)
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

void	write_register(int8_t *program, uint32_t *lc, t_astnode *parameter)
{
	char	*value;

	value = parameter->value;
	if (*value != 'r')
		asm_exit_error("Invalid register");
	value++;
	if (!get_numeric_value(&parameter->num_value, value))
		asm_exit_error("Invalid register");
	if (parameter->num_value < 1 || parameter->num_value > REG_NUMBER)
		asm_exit_error("Invalid register");
	printf("write register %d : %#x\n", parameter->num_value, parameter->num_value);
	write_bytes(program, lc, &parameter->num_value, 1);
}

void	write_direct(int8_t *program, uint32_t *lc,
t_symbol_list symbols, t_astnode *parameter)
{
	t_symbol_list	*label;

	if (parameter->type == INTEGER)
	{
		if (!get_numeric_value(&parameter->num_value, parameter->value))
			asm_exit_error("Invalid direct");
	}
	else
	{
		label = asm_symbol_list_lookup(&symbols, parameter->value);
		if (label == NULL)
			asm_exit_error("Undefined label");
		if (label->node->num_value != 0)
			parameter->num_value = label->node->num_value - *lc;
		else
		{
			//forward reference!
			parameter->num_value = *lc;
		}
	}
	printf("write direct %s %d : %#x\n", g_astnode_types[parameter->type],
		parameter->num_value, parameter->num_value);
	write_bytes(program, lc, &parameter->num_value, 2);
}

void	write_indirect(int8_t *program, uint32_t *lc,
t_symbol_list symbols, t_astnode *parameter)
{
	t_symbol_list	*label;

	if (parameter->type == INTEGER)
	{
		if (!get_numeric_value(&parameter->num_value, parameter->value))
			asm_exit_error("Invalid direct");
	}
	else
	{
		label = asm_symbol_list_lookup(&symbols, parameter->value);
		if (label == NULL)
			asm_exit_error("Undefined label");
		if (label->node->num_value != 0)
			parameter->num_value = label->node->num_value - *lc;
		else
		{
			//forward reference!
			parameter->num_value = *lc;
		}
	}
	printf("write indirect %s %d : %#x\n", g_astnode_types[parameter->type],
		parameter->num_value, parameter->num_value);
	write_bytes(program, lc, &parameter->num_value, 2);
}

void	write_arguments(int8_t *program, uint32_t *lc,
t_symbol_list symbols, t_astnode *parameter_list)
{
	t_astnode	*parameter;

	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (parameter->type == REGISTER)
			write_register(program, lc, parameter);
		else if (parameter->type == INDIRECT)
			write_indirect(program, lc, symbols, parameter->right_child);
		else
			write_direct(program, lc, symbols, parameter->right_child);
		parameter_list = parameter_list->right_child;
	}
}

void	write_argument_coding_byte(int8_t *program, uint32_t *lc,
t_astnode *parameter_list)
{
	t_astnode	*parameter;
	uint8_t		acb;
	uint8_t		i;

	acb = 0;
	i = 6;
	printf("arguments: ");
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		printf("%s ", g_astnode_types[parameter->type]);
		if (parameter->type == REGISTER)
			acb = acb | (REG_CODE << i);
		else if (parameter->type == DIRECT)
			acb = acb | (DIR_CODE << i);
		else if (parameter->type == INDIRECT)
			acb = acb | (IND_CODE << i);
		i -= 2;
		parameter_list = parameter_list->right_child;
	}
	printf("\n=> write argument coding byte %d : %#x\n", acb, acb);
	write_bytes(program, lc, &acb, 1);
}

void	asm_save_label_address(t_output_data *data, uint32_t *lc,
t_symbol_list **labels)
{
	t_symbol_list *symtable_label;

	while (*labels != NULL)
	{
		symtable_label = asm_symbol_list_lookup(&data->symbols, (*labels)->symbol);
		if (symtable_label == NULL)
			asm_exit_error("Label not found from symbol table");
		printf("save address %d : %#x to label '%s'\n", *lc, *lc, symtable_label->symbol);
		symtable_label->node->num_value = (int32_t)*lc;
		asm_symbol_list_delete(labels, (*labels)->symbol);
	}
}

int	asm_generate_instruction(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_op	instruction;

	printf("\nGenerate instruction: %s\n", node->value);
	if (*labels != NULL)
		asm_save_label_address(data, lc, labels);
	get_instruction(&instruction, node->value);
	printf("write opcode %d : %#x\n", instruction.opcode, instruction.opcode);
	write_bytes(data->program, lc, &instruction.opcode, 1);
	if (instruction.has_paramument_coding_byte)
		write_argument_coding_byte(data->program, lc, node->right_child);
	else
		printf("no argument coding byte\n");
	write_arguments(data->program, lc, data->symbols, node->right_child);
	return (1);
}

int	asm_generate_statement(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_astnode	*label;

	label = NULL;
	if (node->left_child != NULL)
		asm_add_label_to_list(labels, node->left_child);
	if (node->right_child != NULL && node->right_child->type == INSTRUCTION)
		return (asm_generate_instruction(data, lc, labels, node->right_child));
	return (1);
}

int	asm_generate_bytecode_program(t_output_data *data, t_astnode *tree)
{
	uint32_t		location_counter;
	t_symbol_list	*labels;
	t_astnode		*statement_list;

	memset(data->program, 0, sizeof(data->program));
	location_counter = 0;
	labels = NULL;
	statement_list = tree->right_child;
	while (statement_list != NULL)
	{
		if (!asm_generate_statement(data, &location_counter,
			&labels, statement_list->left_child))
			return (0);
		statement_list = statement_list->right_child;
	}
	data->header.prog_size = location_counter;
	printf("\n");
	asm_print_symbol_list(&data->symbols, "\nSymbol table after second pass through AST:");
	// resolve forward references to labels
	return (1);
}

int	asm_generate_output(char *input_path, t_output_data *data, t_astnode *tree)
{
	int	ret;

	ret = asm_generate_bytecode_program(data, tree);
	if (!ret)
		return (0);
	asm_write_output_to_file(input_path, data);
	return (1);
}
