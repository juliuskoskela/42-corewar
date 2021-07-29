#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

int	asm_semantic_error(t_astnode *node, char *msg)
{
	dprintf(2, "Semantic error at [%zu, %zu]: %s %s\n",
		node->token.line_no,
		node->token.col,
		msg,
		node->value);
	return (0);
}

int	asm_visit_parameter(t_astnode *node, uint32_t param_nbr, t_op instruction)
{
	uint8_t	type;
	uint8_t	allowed_param_types;

	type = (uint8_t)node->type;
	if (param_nbr == 1)
		allowed_param_types = instruction.param_types.param1;
	else if (param_nbr == 2)
		allowed_param_types = instruction.param_types.param2;
	else
		allowed_param_types = instruction.param_types.param3;
	if ((type & allowed_param_types) == 0)
		return (asm_semantic_error(node->right_child, "Invalid argument type"));
	return (1);
}

int	asm_visit_parameter_list(t_astnode *node, uint32_t param_nbr,
t_op instruction)
{
	int	ret;

	if (param_nbr > instruction.param_count)
		return (asm_semantic_error(node, "Too many arguments for instruction"));
	ret = asm_visit_parameter(node->left_child, param_nbr, instruction);
	if (ret == 1 && node->right_child != NULL)
	{
		ret = asm_visit_parameter_list(node->right_child,
				param_nbr + 1, instruction);
	}
	return (ret);
}

int	asm_visit_instruction(t_astnode *node)
{
	t_op	instruction;

	if (!asm_get_instruction(&instruction, node->value))
		return (asm_semantic_error(node, "Invalid opcode"));
	return (asm_visit_parameter_list(node->right_child, 1, instruction));
}

int	asm_visit_directive(t_astnode *node, t_header *header)
{
	size_t				len;
	char				*dst;
	static const char	*cmd_string[2] = {
		NAME_CMD_STRING,
		COMMENT_CMD_STRING
	};

	if (strcmp(node->left_child->value, &cmd_string[0][1]) == 0)
		dst = header->prog_name;
	else if (strcmp(node->left_child->value, &cmd_string[1][1]) == 0)
		dst = header->comment;
	else
		return (asm_semantic_error(node, "Unrecognized directive"));
	if (dst[0] != '\0')
		return (asm_semantic_error(node, "Duplicate directive"));
	if (node->right_child == NULL)
		return (asm_semantic_error(node, "Missing string for directive"));
	len = strlen(node->right_child->value);
	if ((strcmp(node->left_child->value, &cmd_string[0][1]) == 0
			&& len > PROG_NAME_LENGTH)
		|| (strcmp(node->left_child->value, &cmd_string[1][1]) == 0
			&& len > COMMENT_LENGTH))
		return (asm_semantic_error(node, "String too long for directive"));
	strncpy(dst, node->right_child->value, len);
	return (1);
}

int	asm_visit_label(t_astnode *node, t_symbol_list *symbols)
{
	size_t	i;

	i = 0;
	while (node->value[i] != '\0')
	{
		if (strchr(LABEL_CHARS, node->value[i]) == NULL)
			return (asm_semantic_error(node, "Invalid character in label"));
		i++;
	}
	if (asm_symbol_list_lookup(symbols, node->value) != NULL)
		return (asm_semantic_error(node, "Duplicate definition for label"));
	asm_symbol_list_define(symbols, node);
	return (1);
}

int	asm_visit_statement(t_astnode *node, t_symbol_list *symbols,
t_header *header)
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
	else if (node->right_child != NULL
		&& node->right_child->type == INSTRUCTION)
		ret = asm_visit_instruction(node->right_child);
	if (!ret)
		final_ret = 0;
	return (final_ret);
}

int	asm_visit_statement_list(t_astnode *node, t_symbol_list *symbols,
t_header *header)
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
	int	ret;

	ret = asm_visit_program(tree, &data->symbols, &data->header);
	if (ASM_PRINT_DEBUG)
		asm_print_symbol_list(&data->symbols,
			"Symbol table after first pass through AST:");
	return (ret);
}
