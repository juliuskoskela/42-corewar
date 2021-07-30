#include "asm.h"

t_token	asm_get_id_token(t_lexer *lexer)
{
	t_token		token;
	const char	*token_start;
	size_t		token_len;

	token = asm_init_token(ID_TOKEN, NULL, lexer->line_no, lexer->col);
	token_start = &lexer->input[lexer->current_pos];
	token_len = 0;
	while (is_alpha(lexer->current_char)
		|| is_digit(lexer->current_char)
		|| lexer->current_char == '_')
	{
		asm_lexer_advance(lexer);
		token_len++;
	}
	token.value = s_ndup(token_start, token_len);
	if (token.value == NULL)
		asm_exit_error("Malloc error in allocating token value");
	return (token);
}
