#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include "core.h"

int	main(int argc, char **argv)
{
	t_input_args	arguments;
	char			*input;
	t_astnode		*tree;
	t_output_data	data;

	arguments = asm_parse_arguments(argc, argv);
	input = asm_read_input(arguments.input_path);
	if (input == NULL)
		asm_exit_error("Error on reading input");
	tree = NULL;
	if (!asm_parse(&tree, input))
		asm_exit_error(NULL);
	if (arguments.print_ast_dot)
		asm_write_ast_dot_to_file(arguments.input_path, tree);
	asm_init_output_data(&data);
	if (!asm_validate_ast(&data, tree, arguments.verbose))
		asm_exit_error(NULL);
	asm_generate_output(&data, tree, arguments.verbose);
	asm_write_output_to_file(arguments.input_path, data, arguments.verbose);
	if (arguments.print_hex_dump)
		asm_print_output_hexdump(data);
	asm_astnode_free(tree);
	asm_symbol_list_free(data.symbols);
	free(input);
	return (0);
}
