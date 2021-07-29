#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

static void	asm_print_usage(void)
{
	static const char	*usage = "Usage: ./asm [--dot | --hex-dump] path/to/player.s\n\
	\n\
  --dot:\twrite the intermediate abstract syntax tree to path/to/player.dot\n\
		from which an image can be generated with\n\
		`dot -Tpng -o player_dot.png path/to/player.dot`\n\
  --hex-dump:\tprint the resulting output as a hex dump to standard output";

	printf("%s\n", usage);
	exit(0);
}

int	main(int argc, char **argv)
{
	char			*input;
	t_astnode		*tree;
	t_output_data	data;

	if (argc < 2
		|| strcmp(argv[1], "--help") == 0
		|| strcmp(argv[1], "--usage") == 0)
		asm_print_usage();

	input = asm_read_input(argv[argc - 1]);
	if (input == NULL)
		asm_exit_error("Error on reading input");

	tree = NULL;
	if (!asm_parse(&tree, input))
		asm_exit_error(NULL);

	if (strcmp(argv[1], "--dot") == 0)
		asm_write_ast_dot_to_file(argv[argc - 1], tree);

	asm_init_output_data(&data);
	if (!asm_validate_ast(&data, tree))
		asm_exit_error(NULL);

	asm_generate_output(&data, tree);
	asm_write_output_to_file(argv[argc - 1], data);

	if (strcmp(argv[1], "--hex-dump") == 0)
		asm_print_output_hexdump(data);

	asm_astnode_free(tree);
	asm_symbol_list_free(data.symbols);
	free(input);
	return (0);
}

