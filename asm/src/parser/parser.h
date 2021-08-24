#ifndef PARSER_H
# define PARSER_H

# include "asm.h"

void		asm_init_parser(t_parser *parser, t_lexer *lexer);
void		asm_parser_error(t_parser *parser, t_token_type expected_type);
void		asm_consume_token(t_parser *parser, t_token_type expected_type,
				int	free_token_value);
t_token		asm_init_empty_token(size_t row, size_t col);
t_astnode	*asm_ast_label(t_parser *parser);
t_astnode	*asm_ast_register(t_parser *parser);
t_astnode	*asm_ast_indirect(t_parser *parser);
t_astnode	*asm_ast_direct(t_parser *parser);
t_astnode	*asm_ast_parameter_list(t_parser *parser);
t_astnode	*asm_ast_instruction(t_parser *parser);
t_astnode	*asm_ast_directive(t_parser *parser);
t_astnode	*asm_ast_statement(t_parser *parser);
t_astnode	*asm_ast_statement_list(t_parser *parser);
t_astnode	*asm_ast_program(t_parser *parser);

#endif
