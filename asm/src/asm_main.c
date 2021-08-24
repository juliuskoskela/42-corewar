#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include "core.h"

static void	asm_print_usage(void)
{
	static const char	*usage = "Usage: ./asm [--dot | --hex-dump] path/to/player.s\n\
	\n\
  --dot:\twrite the intermediate abstract syntax tree to path/to/player.dot\n\
		from which an image can be generated with\n\
		`dot -Tpng -o player_dot.png path/to/player.dot`\n\
  --hex-dump:\tprint the resulting output as a hex dump to standard output";

	print("%s\n", usage);
	exit(0);
}

t_input_args	asm_parse_arguments(int argc, char **argv)
{
	t_input_args	arguments;
	int				i;

	if (argc < 2)
		asm_print_usage();
	mset(&arguments, 0, sizeof(arguments));
	i = 1;
	while (i < argc)
	{
		if (s_cmp(argv[1], "--help") == 0 || s_cmp(argv[1], "--usage") == 0)
			asm_print_usage();
		else if (s_cmp(argv[i], "--dot") == 0)
			arguments.print_ast_dot = 1;
		else if (s_cmp(argv[i], "--hex-dump") == 0)
			arguments.print_hex_dump = 1;
		else if (arguments.input_path == NULL)
			arguments.input_path = argv[i];
		else
			asm_print_usage();
		i++;
	}
	return (arguments);
}

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
	asm_parse(&tree, input);
	if (arguments.print_ast_dot)
		asm_write_ast_dot_to_file(arguments.input_path, tree);
	asm_init_output_data(&data);
	asm_validate_ast(&data, tree);
	asm_generate_output(&data, tree);
	asm_write_output_to_file(arguments.input_path, data);
	if (arguments.print_hex_dump)
		asm_print_output_hexdump(data);
	asm_astnode_free(tree);
	asm_symbol_list_free(data.symbols);
	free(input);
	return (0);
}
