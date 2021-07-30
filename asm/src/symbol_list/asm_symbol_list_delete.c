#include "asm.h"
#include "core.h"
#include <stdlib.h>

int	asm_symbol_list_delete(t_symbol_list **list, char *symbol)
{
	t_symbol_list	*node;
	t_symbol_list	*prev;

	node = *list;
	prev = NULL;
	while (node != NULL)
	{
		if (s_cmp(node->symbol, symbol) == 0)
			break ;
		prev = node;
		node = node->next;
	}
	if (node == NULL)
		return (0);
	if (prev == NULL)
		*list = node->next;
	else
		prev->next = node->next;
	free(node);
	return (1);
}
