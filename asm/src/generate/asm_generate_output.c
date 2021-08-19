#include "asm.h"
#include "ast.h"
#include "generate.h"
#include <stdlib.h>
#include "core.h"

static int	asm_generate_bytecode_program(t_output_data *data, t_astnode *tree,
int verbose)
{
	uint32_t		location_counter;
	t_symbol_list	*defined_labels;
	t_astnode		*statement_list;

	location_counter = 0;
	defined_labels = NULL;
	statement_list = tree->right_child;
	while (statement_list != NULL)
	{
		if (!asm_generate_statement(data, &location_counter,
				&defined_labels, statement_list->left_child, verbose))
			return (0);
		statement_list = statement_list->right_child;
	}
	data->header.prog_size = location_counter;
	if (verbose)
		asm_print_symbol_list(&data->symbols,
			"\n\nSymbol table after second pass through AST:");
	return (1);
}

int	asm_generate_output(t_output_data *data, t_astnode *tree, int verbose)
{
	return (asm_generate_bytecode_program(data, tree, verbose));
}
