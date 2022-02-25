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
