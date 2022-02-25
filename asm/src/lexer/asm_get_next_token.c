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
#include "core.h"

static void	asm_lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char == ' ' || lexer->current_char == '\t')
		asm_lexer_advance(lexer);
}

static void	asm_lexer_skip_comment(t_lexer *lexer)
{
	asm_lexer_advance(lexer);
	while (lexer->current_char != '\0' && lexer->current_char != '\n')
		asm_lexer_advance(lexer);
}

static int	asm_is_character_token(char current_char)
{
	if (current_char == '\n' || current_char == '\r'
		|| current_char == '.'
		|| current_char == SEPARATOR_CHAR
		|| current_char == LABEL_CHAR
		|| current_char == DIRECT_CHAR)
		return (1);
	else
		return (0);
}

t_token	asm_get_next_token(t_lexer *lexer)
{
	while (lexer->current_char != '\0')
	{
		if (lexer->current_char == ' ' || lexer->current_char == '\t')
		{
			asm_lexer_skip_whitespace(lexer);
			continue ;
		}
		if (lexer->current_char == COMMENT_CHAR
			|| lexer->current_char == COMMENT_SEMICOLON)
		{
			asm_lexer_skip_comment(lexer);
			continue ;
		}
		if (asm_is_character_token(lexer->current_char))
			return (asm_get_character_token(lexer));
		else if (lexer->current_char == '"')
			return (asm_get_string_token(lexer));
		else if (is_digit(lexer->current_char) || lexer->current_char == '-')
			return (asm_get_int_token(lexer));
		else if (is_alpha(lexer->current_char))
			return (asm_get_id_token(lexer));
		else
			asm_lexer_error(lexer, "Unrecognized token");
	}
	return (asm_get_eof_token(lexer));
}
