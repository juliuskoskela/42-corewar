#include "asm.h"
#include "ast.h"
#include <stdio.h>

void	asm_print_symbol_list(t_symbol_list *symbols, const char *title)
{
	printf("%s\n", title);
	while (symbols != NULL)
	{
		printf("label '%s', value %#x\n",
			symbols->symbol,
			symbols->node->num_value);
		symbols = symbols->next;
	}
	printf("\n");
}

