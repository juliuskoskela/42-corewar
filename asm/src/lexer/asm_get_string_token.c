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

t_token	asm_get_string_token(t_lexer *lexer)
{
	t_token		token;
	const char	*token_start;
	size_t		token_len;

	token = asm_init_token(STRING_TOKEN, NULL, lexer->line_no, lexer->col);
	asm_lexer_advance(lexer);
	token_start = &lexer->input[lexer->current_pos];
	token_len = 0;
	while (lexer->current_char != '"' && lexer->current_char != '\0')
	{
		token_len++;
		asm_lexer_advance(lexer);
	}
	if (lexer->current_char != '"')
		asm_lexer_error(lexer, "Missing terminating '\"' character");
	asm_lexer_advance(lexer);
	token.value = s_ndup(token_start, token_len);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	return (token);
}
