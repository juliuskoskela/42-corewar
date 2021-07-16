#include "asm.h"
#include <stdio.h>

int	asm_parse(t_lexer *lexer)
{
	t_token token;

	token = asm_get_next_token(lexer);
	while (token.type != EOF_TOKEN && token.type != ERROR)
	{
		printf("Token:\n\ttype: %d\n\tvalue: %s\n\n", token.type, token.value);
		token = asm_get_next_token(lexer);
	}
	if (token.type == ERROR)
	{
		printf("Token error\n");
		return (0);
	}
	else
		printf("EOF\n");
	return (1);
}