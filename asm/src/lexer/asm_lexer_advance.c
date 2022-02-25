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

void	asm_lexer_advance(t_lexer *lexer)
{
	lexer->current_pos++;
	lexer->current_char = lexer->input[lexer->current_pos];
	if (lexer->current_char == '\n' || lexer->current_char == '\r')
	{
		lexer->line_no++;
		lexer->col = 1;
	}
	else
		lexer->col++;
}
