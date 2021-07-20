#include "asm.h"
#include "ast.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

int	asm_symbol_list_delete(t_symbol_list **list, char *symbol)
{
	t_symbol_list	*node;
	t_symbol_list	*prev;

	node = *list;
	prev = NULL;
	while (node != NULL)
	{
		if (strcmp(node->symbol, symbol) == 0)
			break ;
		prev = node;
		node = node->next;
	}
	if (node == NULL)
		return (0);
	if (prev == NULL)
		*list = node->next;
	else
		prev->next = node->next;
	free(node);
	return (1);
}

t_op	get_instruction(char *mnemonic)
{
	size_t	i;

	i = 0;
	while (i < OP_COUNT)
	{
		if (strcmp(mnemonic, g_op_tab[i].mnemonic) == 0)
			break ;
		i++;
	}
	return (g_op_tab[i]);
}

void	write_byte(int8_t *program, uint32_t *lc, int8_t byte)
{
	if (*lc == CHAMP_MAX_SIZE)
		asm_exit_error("Program too large");
	program[*lc] = byte;
	*lc = *lc + 1;
}

void	write_argument_coding_byte(int8_t *program, uint32_t *lc, t_astnode *parameter_list)
{
	t_astnode	*parameter;
	int8_t		acb;
	int8_t		i;

	acb = 0;
	i = 3;
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
		i--;
		parameter_list = parameter_list->right_child;
	}
	printf("=> argument coding byte %#x\n", acb);
	write_byte(program, lc, acb);
}

void	write_arguments(int8_t *program, uint32_t *lc, t_astnode *parameter_list)
{
	t_astnode	*parameter;

	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		//resolve numeric value
		write_byte(program, lc, parameter->num_value);
		parameter_list = parameter_list->right_child;
	}
}

int	asm_generate_instruction(t_output_data *data, uint32_t *lc, t_symbol_list **labels, t_astnode *node)
{
	t_op	instruction;

	if (*labels != NULL)
		printf("to do:resolve label\n");
	instruction = get_instruction(node->value);
	write_byte(data->program, lc, instruction.opcode);
	if (instruction.has_paramument_coding_byte)
		write_argument_coding_byte(data->program, lc, node->right_child);
	else
		printf("no argument coding byte\n");
	write_arguments(data->program, lc, node->right_child);
	return (1);
}

int	asm_generate_statement(t_output_data *data, uint32_t *lc, t_symbol_list **labels, t_astnode *node)
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

	location_counter = 0;
	labels = NULL;
	statement_list = tree->right_child;
	while (statement_list != NULL)
	{
		if (!asm_generate_statement(data, &location_counter, &labels, statement_list->left_child))
			return (0);
		statement_list = statement_list->right_child;
	}
	data->header.prog_size = location_counter;
	// resolve label arguments
	return (1);
}

void	asm_write_header_to_file(int fd, t_header header)
{
	printf("write magic %u : %#x\n", header.magic, header.magic);
	write(fd, (void *)&header.magic, sizeof(header.magic));
	printf("write prog_name '%s'\n", header.prog_name);
	write(fd, header.prog_name, sizeof(header.prog_name));
	printf("write prog_size %u : %#x\n", header.prog_size, header.prog_size);
	write(fd, (void *)&header.prog_size, sizeof(header.prog_size));
	printf("write comment '%s'\n", header.comment);
	write(fd, header.comment, sizeof(header.comment));
}

void	asm_write_program_to_file(int fd, t_output_data *data)
{
	printf("write program of size %u\n", data->header.prog_size);
	write(fd, data->program, data->header.prog_size);
}

void	asm_write_output_to_file(char *path, t_output_data *data)
{
	char	*cor_file;
	size_t	path_len;
	size_t	file_name_len;
	int		fd;

	path_len = strlen(path);
	file_name_len = path_len + 2;
	cor_file = (char *)malloc(sizeof(char) * (file_name_len + 1));
	strcpy(cor_file, path);
	strcpy(&cor_file[path_len - 1], "cor");
	fd = open(cor_file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		asm_exit_error("Error on writing output to .cor file");
	printf("\nWriting output to %s\n", cor_file);
	asm_write_header_to_file(fd, data->header);
	asm_write_program_to_file(fd, data);
	close(fd);
}

int	asm_generate_output(char *input_path, t_output_data *data, t_astnode *tree)
{
	int	ret;

	memset(data->program, 0, sizeof(data->program));
	// write instructions to data->program one at a time
	// 1) opcode
	// 2) argument coding byte
	// 3) numeric values of parameters
	ret = asm_generate_bytecode_program(data, tree);
	if (!ret)
		return (0);
	// create output file & write output
	asm_write_output_to_file(input_path, data);
	return (1);
}
