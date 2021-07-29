#include "asm.h"
#include "ast.h"
#include <stdlib.h>

void	asm_astnode_free(t_astnode *tree)
{
	if (tree->left_child != NULL)
		asm_astnode_free(tree->left_child);
	if (tree->right_child != NULL)
		asm_astnode_free(tree->right_child);
	free(tree->token.value);
	free(tree);
}

