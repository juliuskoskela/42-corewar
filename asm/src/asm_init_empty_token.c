#include "asm.h"

t_token	asm_init_empty_token(size_t row, size_t col)
{
	t_token	token;

	token.type = NO_TOKEN;
	token.value = NULL;
	token.line_no = row;
	token.col = col;
	return (token);
}

