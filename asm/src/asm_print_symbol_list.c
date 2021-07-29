#include "asm.h"
#include "ast.h"
#include "core.h"

void	asm_print_symbol_list(t_symbol_list *symbols, const char *title)
{
	print("%s\n", title);
	while (symbols != NULL)
	{
		print("label '%s', value %#x\n",
			symbols->symbol,
			symbols->node->num_value);
		symbols = symbols->next;
	}
	print("\n");
}
