#include "asm.h"

t_token	asm_init_token(t_token_type type, char *value, size_t row, size_t col)
{
	t_token	token;

	token.type = type;
	token.value = value;
	token.file_row = row;
	token.file_col = col;
	return (token);
}
