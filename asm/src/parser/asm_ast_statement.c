/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ast.h"
#include "parser.h"

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
