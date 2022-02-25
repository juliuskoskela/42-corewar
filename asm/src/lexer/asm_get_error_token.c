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
#include "lexer.h"

t_token	asm_get_error_token(t_lexer *lexer)
{
	t_token	token;

	token = asm_init_token(ERROR_TOKEN, NULL, lexer->line_no, lexer->col);
	token.value = s_ndup(&lexer->input[lexer->current_pos], 1);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	asm_lexer_advance(lexer);
	return (token);
}
