#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

void	asm_print_semantic_error(t_astnode *node, char *msg)
{
	dprintf(2, "Semantic error at [%zu, %zu]: %s\n",
		node->token.file_row,
		node->token.file_col,
		msg);
}

int	asm_visit_parameter(t_astnode *node, uint32_t param_number, t_op instruction)
{
	uint8_t	type;

	type = (uint8_t)node->type;
	if ((param_number == 1 && ((type & instruction.param_types.param1) == 0))
		|| (param_number == 2 && ((type & instruction.param_types.param2) == 0))
		|| (param_number == 3 && ((type & instruction.param_types.param3) == 0)))
	{
		asm_print_semantic_error(node, "Invalid argument type");
		return (0);
	}
	return (1);
}

int	asm_visit_parameter_list(t_astnode *node, uint32_t param_number, t_op instruction)
{
	int	ret;

	if (param_number > instruction.param_count)
	{
		asm_print_semantic_error(node, "Too many arguments for instruction");
		return (0);
	}
	ret = asm_visit_parameter(node->left_child, param_number, instruction);
	if (ret == 1 && node->right_child != NULL)
		return (asm_visit_parameter_list(node->right_child, param_number + 1, instruction));
	else
		return (ret);
}

int	asm_visit_instruction(t_astnode *node)
{
	size_t	op_index;
	t_op	instruction;

	op_index = 0;
	while (g_op_tab[op_index].mnemonic != 0)
	{
		if (strcmp(g_op_tab[op_index].mnemonic, node->value) == 0)
			break ;
		op_index++;
	}
	if (g_op_tab[op_index].mnemonic == 0)
	{
		printf("op_index %d\n", (int)op_index);
		asm_print_semantic_error(node, "Invalid opcode");
		return (0);
	}
	instruction = g_op_tab[op_index];
	return (asm_visit_parameter_list(node->right_child, 1, instruction));
}

int	asm_visit_directive(t_astnode *node, t_header *header)
{
	size_t				len;
	static const char	*cmd_string[2] = {
		NAME_CMD_STRING,
		COMMENT_CMD_STRING
	};

	if (strcmp(node->left_child->value, &cmd_string[0][1]) == 0)
	{
		if (header->prog_name[0] != '\0')
		{
			asm_print_semantic_error(node, "Duplicate name directive");
			return (0);
		}
		if (node->right_child == NULL)
		{
			asm_print_semantic_error(node, "Missing string for name directive");
			return (0);
		}
		len = strlen(node->right_child->value);
		if (len > PROG_NAME_LENGTH)
		{
			asm_print_semantic_error(node, "Program name too long");
			return (0);
		}
		strncpy(header->prog_name, node->right_child->value, len);
		return (1);
	}
	else if (strcmp(node->left_child->value, &cmd_string[1][1]) == 0)
	{
		if (header->comment[0] != '\0')
		{
			asm_print_semantic_error(node, "Duplicate comment directive");
			return (0);
		}
		if (node->right_child == NULL)
		{
			asm_print_semantic_error(node, "Missing string for comment directive");
			return (0);
		}
		len = strlen(node->right_child->value);
		if (len > COMMENT_LENGTH)
		{
			asm_print_semantic_error(node, "Comment too long");
			return (0);
		}
		strncpy(header->comment, node->right_child->value, len);
		return (1);
	}
	else
	{
		asm_print_semantic_error(node, "Unrecognized directive:");
		printf("%s\n\n", node->left_child->value);
		return (0);
	}
}

int	asm_visit_label(t_astnode *node, t_symbol_list *symbols)
{
	size_t	i;

	i = 0;
	while (node->value[i] != '\0')
	{
		if (strchr(LABEL_CHARS, node->value[i]) == NULL)
		{
			asm_print_semantic_error(node, "Invalid character in label name");
			return (0);
		}
		i++;
	}
	if (asm_symbol_list_lookup(symbols, node->value) != NULL)
	{
		asm_print_semantic_error(node, "Duplicate definition for label");
		return (0);
	}
	asm_symbol_list_define(symbols, node);
	return (1);
}

int	asm_visit_statement(t_astnode *node, t_symbol_list *symbols, t_header *header)
{
	int	ret;
	int	final_ret;

	ret = 1;
	final_ret = 1;
	if (node->left_child != NULL)
		ret = asm_visit_label(node->left_child, symbols);
	if (!ret)
		final_ret = 0;
	if (node->right_child != NULL && node->right_child->type == DIRECTIVE)
		ret = asm_visit_directive(node->right_child, header);
	else if (node->right_child != NULL && node->right_child->type == INSTRUCTION)
		ret = asm_visit_instruction(node->right_child);
	if (!ret)
		final_ret = 0;
	return (final_ret);
}

int	asm_visit_statement_list(t_astnode *node, t_symbol_list *symbols, t_header *header)
{
	int	ret;
	int	final_ret;

	ret = 1;
	final_ret = 1;
	if (node->left_child != NULL)
		ret = asm_visit_statement(node->left_child, symbols, header);
	if (!ret)
		final_ret = 0;
	if (node->right_child != NULL)
		ret = asm_visit_statement_list(node->right_child, symbols, header);
	if (!ret)
		final_ret = 0;
	return (final_ret);
}

int	asm_visit_program(t_astnode *node, t_symbol_list *symbols, t_header *header)
{
	int	ret;

	ret = 1;
	if (node->right_child != NULL)
		ret = asm_visit_statement_list(node->right_child, symbols, header);
	return (ret);
}

int	asm_validate_ast(t_output_data *data, t_astnode *tree)
{
	int				ret;

	memset(&data->header, 0, sizeof(t_header));
	memset(&data->symbols, 0, sizeof(t_symbol_list));
	data->header.magic = COREWAR_EXEC_MAGIC;
	ret = asm_visit_program(tree, &data->symbols, &data->header);
	asm_print_symbol_list(&data->symbols, "Symbol table after first pass through AST:");
	return (ret);
}
