#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

int	asm_parser_error(t_parser *parser, t_token_type expected_type)
{
	dprintf(2, "Syntax error at [%zu, %zu]: token '%s' of type %s\
 does not match expected type %s\n",
		parser->current_token.line_no,
		parser->current_token.col,
		parser->current_token.value,
		g_token_types[parser->current_token.type],
		g_token_types[expected_type]);
	parser->error_occurred = 1;
	return (0);
}

int	asm_consume_token(t_parser *parser, t_token_type expected_type,
int free_token_value)
{
	if (parser->current_token.type == expected_type)
	{
		if (free_token_value)
			free(parser->current_token.value);
		parser->current_token = asm_get_next_token(parser->lexer);
		return (1);
	}
	else
	{
		asm_parser_error(parser, expected_type);
		if (free_token_value)
			free(parser->current_token.value);
		parser->current_token = asm_get_next_token(parser->lexer);
		return (0);
	}
}

t_astnode	*asm_ast_label(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(LABEL,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	asm_consume_token(parser, LABEL_TOKEN, 1);
	return (node);
}

t_astnode	*asm_ast_register(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(REGISTER,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	return (node);
}

t_astnode	*asm_ast_indirect(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(INDIRECT, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	if (parser->current_token.type == INTEGER_TOKEN)
	{
		node->right_child = asm_astnode_new(INTEGER,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, INTEGER_TOKEN, 0);
	}
	else
	{
		asm_consume_token(parser, LABEL_TOKEN, 1);
		node->right_child = asm_astnode_new(LABEL,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, ID_TOKEN, 0);
	}
	return (node);
}

t_astnode	*asm_ast_direct(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(DIRECT, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	asm_consume_token(parser, DIRECT_TOKEN, 1);
	if (parser->current_token.type == INTEGER_TOKEN)
	{
		node->right_child = asm_astnode_new(INTEGER,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, INTEGER_TOKEN, 0);
	}
	else
	{
		asm_consume_token(parser, LABEL_TOKEN, 1);
		node->right_child = asm_astnode_new(LABEL,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, ID_TOKEN, 0);
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

	node = asm_astnode_new(PARAMETER_LIST, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	node->left_child = asm_ast_parameter(parser);
	if (parser->current_token.type == SEPARATOR_TOKEN)
	{
		asm_consume_token(parser, SEPARATOR_TOKEN, 1);
		node->right_child = asm_ast_parameter_list(parser);
	}
	return (node);
}

t_astnode	*asm_ast_instruction(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(INSTRUCTION,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	node->right_child = asm_ast_parameter_list(parser);
	return (node);
}

t_astnode	*asm_ast_directive(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(DIRECTIVE, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	asm_consume_token(parser, DOT_TOKEN, 1);
	node->left_child = asm_astnode_new(CMD,
			parser->current_token.value, parser->current_token);
	asm_consume_token(parser, ID_TOKEN, 0);
	if (parser->current_token.type == STRING_TOKEN)
	{
		node->right_child = asm_astnode_new(CMD_STRING,
				parser->current_token.value, parser->current_token);
		asm_consume_token(parser, STRING_TOKEN, 0);
	}
	return (node);
}

t_astnode	*asm_ast_statement(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(STATEMENT, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	if (asm_peek_next_token(parser->lexer) == LABEL_TOKEN)
		node->left_child = asm_ast_label(parser);
	if (parser->current_token.type == DOT_TOKEN)
		node->right_child = asm_ast_directive(parser);
	else if (parser->current_token.type == ID_TOKEN)
		node->right_child = asm_ast_instruction(parser);
	asm_consume_token(parser, NEWLINE_TOKEN, 1);
	while (parser->current_token.type == NEWLINE_TOKEN)
		asm_consume_token(parser, NEWLINE_TOKEN, 1);
	return (node);
}

t_astnode	*asm_ast_statement_list(t_parser *parser)
{
	t_astnode	*list_node;

	list_node = asm_astnode_new(STATEMENT_LIST, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
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

	program_node = asm_astnode_new(PROGRAM, "",
			asm_init_empty_token(parser->current_token.line_no,
				parser->current_token.col));
	program_node->right_child = asm_ast_statement_list(parser);
	return (program_node);
}

int	asm_parse(t_astnode **tree, char *input)
{
	t_lexer			lexer;
	t_parser		parser;

	asm_init_lexer(&lexer, input);
	asm_init_parser(&parser, &lexer);
	*tree = asm_ast_program(&parser);
	if (parser.error_occurred)
		return (0);
	return (1);
}

