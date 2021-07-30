#include "asm.h"
#include "lexer.h"

static t_token	asm_get_decimal_token(t_lexer *lexer)
{
	t_token		token;
	const char	*token_start;
	size_t		token_len;

	token = asm_init_token(INTEGER_TOKEN, NULL, lexer->line_no, lexer->col);
	token_start = &lexer->input[lexer->current_pos];
	token_len = 0;
	if (lexer->current_char == '-' && !is_digit(asm_lexer_peek(lexer)))
	{
		token.type = ERROR_TOKEN;
		asm_print_lexer_error(lexer, "Unrecognized token");
	}
	if (lexer->current_char == '-')
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	while (is_digit(lexer->current_char))
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	token.value = s_ndup(token_start, token_len);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	return (token);
}

static t_token	asm_get_hex_token(t_lexer *lexer)
{
	t_token		token;
	const char	*token_start;
	size_t		token_len;

	token = asm_init_token(INTEGER_TOKEN, NULL, lexer->line_no, lexer->col);
	token_start = &lexer->input[lexer->current_pos];
	asm_lexer_advance(lexer);
	asm_lexer_advance(lexer);
	if (!is_digit(lexer->current_char)
		 && lexer->current_char < 'a' && lexer->current_char > 'f')
	{
		token.type = ERROR_TOKEN;
		asm_print_lexer_error(lexer, "Unrecognized token");
	}
	token_len = 2;
	while (is_digit(lexer->current_char)
		|| (lexer->current_char >= 'a' && lexer->current_char <= 'f'))
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	token.value = s_ndup(token_start, token_len);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	return (token);
}

t_token	asm_get_int_token(t_lexer *lexer)
{
	if (lexer->current_char == '0' && asm_lexer_peek(lexer) == 'x')
		return (asm_get_hex_token(lexer));
	else
		return (asm_get_decimal_token(lexer));
}
