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

t_token	asm_get_character_token(t_lexer *lexer)
{
	t_token	token;

	token = asm_init_token(ERROR_TOKEN, NULL, lexer->line_no, lexer->col);
	if (lexer->current_char == '\n' || lexer->current_char == '\r')
		token.type = NEWLINE_TOKEN;
	else if (lexer->current_char == '.')
		token.type = DOT_TOKEN;
	else if (lexer->current_char == SEPARATOR_CHAR)
		token.type = SEPARATOR_TOKEN;
	else if (lexer->current_char == LABEL_CHAR)
		token.type = LABEL_TOKEN;
	else if (lexer->current_char == DIRECT_CHAR)
		token.type = DIRECT_TOKEN;
	token.value = s_ndup(&lexer->input[lexer->current_pos], 1);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	asm_lexer_advance(lexer);
	return (token);
}
