#include "asm.h"
#include "ast.h"
#include "core.h"
#include <stdlib.h>

void	asm_generate_error(t_astnode *node, char *msg)
{
	print_fd(2, "Semantic error at [%u, %u]: %s %s\n",
		node->token.line_no,
		node->token.col,
		msg,
		node->value);
	exit(1);
}
