#include "asm.h"
#include <stdlib.h>

t_symbol_list	*asm_symbol_list_lookup(t_symbol_list *list, char *symbol)
{
	while (list != NULL)
	{
		if (list->symbol != NULL && strcmp(list->symbol, symbol) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
