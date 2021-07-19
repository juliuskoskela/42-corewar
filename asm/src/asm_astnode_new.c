#include "asm.h"
#include <stdlib.h>

t_astnode	*astnode_new(t_astnode_type type, char *value)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		asm_exit_error("Malloc error in allocating AST node");
	node->type = type;
	node->value = value;
	node->left_child = NULL;
	node->right_child = NULL;
	return (node);
}
