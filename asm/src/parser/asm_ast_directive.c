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
