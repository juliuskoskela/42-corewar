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
#include "core.h"

void	asm_parser_error(t_parser *parser, t_token_type expected_type)
{
	print_fd(2, "Syntax error at [%u, %u]: token '%s' of type %s\
 does not match expected type %s\n",
		parser->current_token.line_no,
		parser->current_token.col,
		parser->current_token.value,
		g_token_types[parser->current_token.type],
		g_token_types[expected_type]);
	parser->error_occurred = 1;
	exit(1);
}
