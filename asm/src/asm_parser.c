#include "asm.h"
#include <stdlib.h>
#include <stdio.h>

int	asm_consume_token(t_parser *parser, t_token_type expected_type)
{
	if (parser->current_token.type == expected_type)
	{
		parser->current_token = asm_get_next_token(parser->lexer);
		return (1);
	}
	else
	{
		dprintf(2, "Parser error at [%zu, %zu]: token '%s' of type %s does not match expected type %s\n",
			parser->current_token.file_row,
			parser->current_token.file_col,
			parser->current_token.value,
			g_token_types[parser->current_token.type],
			g_token_types[expected_type]);
		parser->error_occurred = 1;
		return (0);
	}
}

t_astnode	*asm_ast_label(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(LABEL, parser->current_token.value);
	asm_consume_token(parser, ID_TOKEN);
	asm_consume_token(parser, LABEL_TOKEN);
	return (node);
}

t_astnode	*asm_ast_register(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(REGISTER, parser->current_token.value);
	asm_consume_token(parser, ID_TOKEN);
	return (node);
}

t_astnode	*asm_ast_indirect(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(INDIRECT, "");
	if (parser->current_token.type == INTEGER_TOKEN)
	{
		node->left_child = astnode_new(INTEGER, parser->current_token.value);
		asm_consume_token(parser, INTEGER_TOKEN);
	}
	else
	{
		asm_consume_token(parser, LABEL_TOKEN);
		node->left_child = astnode_new(LABEL, parser->current_token.value);
		asm_consume_token(parser, ID_TOKEN);
	}
	return (node);
}

t_astnode	*asm_ast_direct(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(DIRECT, "");
	asm_consume_token(parser, DIRECT_TOKEN);
	if (parser->current_token.type == INTEGER_TOKEN)
	{
		node->left_child = astnode_new(INTEGER, parser->current_token.value);
		asm_consume_token(parser, INTEGER_TOKEN);
	}
	else
	{
		asm_consume_token(parser, LABEL_TOKEN);
		node->left_child = astnode_new(LABEL, parser->current_token.value);
		asm_consume_token(parser, ID_TOKEN);
	}
	return (node);
}

t_astnode	*asm_ast_parameter(t_parser *parser)
{
	if (parser->current_token.type == DIRECT_TOKEN)
		return (asm_ast_direct(parser));
	else if (parser->current_token.type == INTEGER_TOKEN
		|| parser->current_token.type == LABEL_TOKEN)
		return (asm_ast_indirect(parser));
	else
		return (asm_ast_register(parser));
}

t_astnode	*asm_ast_parameter_list(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(PARAMETER_LIST, "");
	node->left_child = asm_ast_parameter(parser);
	if (parser->current_token.type == SEPARATOR_TOKEN)
	{
		asm_consume_token(parser, SEPARATOR_TOKEN);
		node->right_child = asm_ast_parameter_list(parser);
	}
	return (node);
}

t_astnode	*asm_ast_instruction(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(INSTRUCTION, parser->current_token.value);
	asm_consume_token(parser, ID_TOKEN);
	node->right_child = asm_ast_parameter_list(parser);
	return (node);
}

t_astnode	*asm_ast_directive(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(DIRECTIVE, "");
	asm_consume_token(parser, DOT_TOKEN);
	node->left_child = astnode_new(CMD, parser->current_token.value);
	asm_consume_token(parser, ID_TOKEN);
	if (parser->current_token.type == STRING_TOKEN)
	{
		node->right_child = astnode_new(CMD_STRING, parser->current_token.value);
		asm_consume_token(parser, STRING_TOKEN);
	}
	return (node);
}

t_astnode	*asm_ast_statement(t_parser *parser)
{
	t_astnode	*node;

	node = astnode_new(STATEMENT, "");
	if (asm_peek_next_token(parser->lexer) == LABEL_TOKEN)
		node->left_child = asm_ast_label(parser);
	if (parser->current_token.type == DOT_TOKEN)
		node->right_child = asm_ast_directive(parser);
	else if (parser->current_token.type == ID_TOKEN)
		node->right_child = asm_ast_instruction(parser);
	asm_consume_token(parser, NEWLINE_TOKEN);
	while (parser->current_token.type == NEWLINE_TOKEN)
		asm_consume_token(parser, NEWLINE_TOKEN);
	return (node);
}

t_astnode	*asm_ast_statement_list(t_parser *parser)
{
	t_astnode	*list_node;

	list_node = astnode_new(STATEMENT_LIST, "");
	list_node->left_child = asm_ast_statement(parser);
	if (parser->current_token.type != EOF_TOKEN
		&& parser->current_token.type != ERROR_TOKEN)
	{
		list_node->right_child = asm_ast_statement_list(parser);
	}
	return (list_node);
}

t_astnode	*asm_ast_program(t_parser *parser)
{
	t_astnode	*program_node;

	program_node = astnode_new(PROGRAM, "");
	program_node->left_child = asm_ast_statement_list(parser);
	return (program_node);
}

int	asm_parse(t_astnode **tree, t_parser *parser)
{
	*tree = asm_ast_program(parser);
	if (parser->error_occurred)
		return (0);
	else
		return (1);
}
