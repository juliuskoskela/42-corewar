#include "asm.h"

void	asm_lexer_error(t_lexer *lexer, const char *msg)
{
	print_fd(2, "Lexer error at [%u, %u]: %s\n",
		lexer->line_no,
		lexer->col,
		msg);
	exit(0);
}
