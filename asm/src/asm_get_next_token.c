#include "asm.h"
#include <ctype.h>

void	asm_lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char == ' ' || lexer->current_char == '\t')
		asm_lexer_advance(lexer);
}

void	asm_lexer_skip_comment(t_lexer *lexer)
{
	asm_lexer_advance(lexer);
	while (lexer->current_char != '\0' && lexer->current_char != '\n')
		asm_lexer_advance(lexer);
}

t_token	asm_get_eof_token(void)
{
	t_token	next_token;

	next_token.type = EOF_TOKEN;
	next_token.value = NULL;
	return (next_token);
}

t_token	asm_get_error_token(void)
{
	t_token	next_token;

	next_token.type = ERROR_TOKEN;
	next_token.value = NULL;
	return (next_token);
}

t_token	asm_get_int_token(t_lexer *lexer)
{
	t_token		next_token;
	const char	*token_start;
	size_t		token_len;

	next_token.type = INTEGER_TOKEN;
	token_start = &lexer->input[lexer->current_pos];
	token_len = 0;
	if (lexer->current_char == '-')
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	while (isdigit(lexer->current_char))
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	next_token.value = strndup(token_start, token_len);
	return (next_token);
}

t_token	asm_get_id_token(t_lexer *lexer)
{
	t_token		next_token;
	const char	*token_start;
	size_t		token_len;

	next_token.type = ID_TOKEN;
	token_start = &lexer->input[lexer->current_pos];
	token_len = 0;
	while (isalpha(lexer->current_char)
		|| isdigit(lexer->current_char)
		|| lexer->current_char == '_')
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	next_token.value = strndup(token_start, token_len);
	return (next_token);
}

t_token	asm_get_dot_token(t_lexer *lexer)
{
	t_token		next_token;
	const char	*token_start;
	size_t		token_len;

	next_token.type = DOT_CMD_TOKEN;
	token_start = &lexer->input[lexer->current_pos];
	asm_lexer_advance(lexer);
	token_len = 1;
	while (isalpha(lexer->current_char)
		|| isdigit(lexer->current_char)
		|| lexer->current_char == '_')
	{
		token_len++;
		asm_lexer_advance(lexer);
	}
	next_token.value = strndup(token_start, token_len);
	return (next_token);
}

t_token	asm_get_string_token(t_lexer *lexer)
{
	t_token		next_token;
	const char	*token_start;
	size_t		token_len;

	next_token.type = STRING_TOKEN;
	token_start = &lexer->input[lexer->current_pos];
	asm_lexer_advance(lexer);
	token_len = 1;
	while (lexer->current_char != '"' && lexer->current_char != '\0')
	{
		token_len++;
		asm_lexer_advance(lexer);
	}
	if (lexer->current_char != '"')
	{
		next_token.type = ERROR_TOKEN;
		next_token.value = NULL;
	}
	else
	{
		token_len++;
		asm_lexer_advance(lexer);
		next_token.value = strndup(token_start, token_len);
	}
	return (next_token);
}

t_token	asm_get_character_token(t_lexer *lexer)
{
	t_token	next_token;

	if (lexer->current_char == '\n' || lexer->current_char == '\r')
		next_token.type = NEWLINE_TOKEN;
	else if (lexer->current_char == SEPARATOR_CHAR)
		next_token.type = SEPARATOR_TOKEN;
	else if (lexer->current_char == LABEL_CHAR)
		next_token.type = LABEL_TOKEN;
	else
		next_token.type = DIRECT_TOKEN;
	next_token.value = strndup(&lexer->input[lexer->current_pos], 1);
	asm_lexer_advance(lexer);
	return (next_token);
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
		if (lexer->current_char == COMMENT_CHAR)
		{
			asm_lexer_skip_comment(lexer);
			continue ;
		}
		if (lexer->current_char == '\n' || lexer->current_char == '\r'
			|| lexer->current_char == SEPARATOR_CHAR
			|| lexer->current_char == LABEL_CHAR
			|| lexer->current_char == DIRECT_CHAR)
			return (asm_get_character_token(lexer));
		else if (lexer->current_char == '.')
			return (asm_get_dot_token(lexer));
		else if (lexer->current_char == '"')
			return (asm_get_string_token(lexer));
		else if (isdigit(lexer->current_char) || lexer->current_char == '-')
			return (asm_get_int_token(lexer));
		else if (isalpha(lexer->current_char))
			return (asm_get_id_token(lexer));
		else
			return (asm_get_error_token());
	}
	return (asm_get_eof_token());
}
