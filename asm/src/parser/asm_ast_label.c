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

t_astnode	*asm_ast_label(t_parser *parser)
{
	t_astnode	*node;

	node = asm_astnode_new(LABEL,
			parser->current_token.value, parser->current_token);
	node->num_value = -1;
	asm_consume_token(parser, ID_TOKEN, 0);
	asm_consume_token(parser, LABEL_TOKEN, 1);
	return (node);
}
