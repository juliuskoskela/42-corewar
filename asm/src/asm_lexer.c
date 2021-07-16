#include "asm.h"
#include <ctype.h>

t_lexer	asm_init_lexer(const char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.current_pos = 0;
	lexer.current_char = input[0];
	return (lexer);
}

void	asm_lexer_advance(t_lexer *lexer)
{
	lexer->current_pos++;
	lexer->current_char = lexer->input[lexer->current_pos];
}

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

t_token	asm_get_next_token(t_lexer *lexer)
{
	t_token		next_token;
	const char	*token_start;
	size_t		token_len;

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
		if (lexer->current_char == '\n' || lexer->current_char == '\r')
		{
			next_token.type = NEWLINE;
			next_token.value = strndup(&lexer->input[lexer->current_pos], 1);
			asm_lexer_advance(lexer);
			return (next_token);
		}
		else if (lexer->current_char == '.')
		{
			next_token.type = DOT_CMD;
			token_start = &lexer->input[lexer->current_pos];
			asm_lexer_advance(lexer);
			token_len = 1;
			while (isalpha(lexer->current_char))
			{
				token_len++;
				asm_lexer_advance(lexer);
			}
			next_token.value = strndup(token_start, token_len);
			return (next_token);
		}
		else if (lexer->current_char == '"')
		{
			next_token.type = STRING;
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
				next_token.type = ERROR;
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
		else if (lexer->current_char == SEPARATOR_CHAR)
		{
			next_token.type = SEPARATOR;
			next_token.value = strndup(&lexer->input[lexer->current_pos], 1);
			asm_lexer_advance(lexer);
			return (next_token);
		}
		else if (lexer->current_char == LABEL_CHAR)
		{
			next_token.type = LABEL;
			next_token.value = strndup(&lexer->input[lexer->current_pos], 1);
			asm_lexer_advance(lexer);
			return (next_token);
		}
		else if (lexer->current_char == DIRECT_CHAR)
		{
			next_token.type = DIRECT;
			next_token.value = strndup(&lexer->input[lexer->current_pos], 1);
			asm_lexer_advance(lexer);
			return (next_token);
		}
		else if (isdigit(lexer->current_char))
		{
			next_token.type = INTEGER;
			token_start = &lexer->input[lexer->current_pos];
			token_len = 0;
			while (isdigit(lexer->current_char))
			{
				asm_lexer_advance(lexer);
				token_len++;
			}
			next_token.value = strndup(token_start, token_len);
			return (next_token);
		}
		else if (isalpha(lexer->current_char))
		{
			next_token.type = ID;
			token_start = &lexer->input[lexer->current_pos];
			token_len = 0;
			while (isalpha(lexer->current_char) || isdigit(lexer->current_char))
			{
				asm_lexer_advance(lexer);
				token_len++;
			}
			next_token.value = strndup(token_start, token_len);
			return (next_token);
		}
		else
		{
			next_token.type = ERROR;
			next_token.value = NULL;
			return (next_token);
		}
	}
	next_token.type = EOF_TOKEN;
	next_token.value = NULL;
	return (next_token);
}
