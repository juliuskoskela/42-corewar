#include "asm.h"
#include <stdlib.h>

void	asm_symbol_list_free(t_symbol_list list)
{
	t_symbol_list	*node;
	t_symbol_list	*next;

	node = list.next;
	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

