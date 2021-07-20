#include "asm.h"
#include <stdio.h>

void	asm_print_symbol_list(t_symbol_list *symbols)
{
	printf("Symbol table:\n");
	while (symbols != NULL)
	{
		printf("%s\n", symbols->symbol);
		symbols = symbols->next;
	}
	printf("\n");
}
