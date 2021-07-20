#include "asm.h"
#include <stdlib.h>
#include <stdio.h>

static void	asm_print_usage(void)
{
	static const char *usage = "Usage: ./asm [--dot] path/to/player.s\n\
	\n\
	--dot : write the intermediate abstract syntax tree to path/to/player.dot\n\
		from which an image can be generated with\n\
		`dot -Tpng -o player_dot.png path/to/player.dot`";

	printf("%s\n", usage);
	exit(0);
}

int	main(int argc, char **argv)
{
	char			*input;
	t_lexer			lexer;
	t_parser		parser;
	t_astnode		*tree;
	t_output_data	data;

	if (argc < 2)
		asm_print_usage();

	input = asm_read_input(argv[argc - 1]);
	if (input == NULL)
		asm_exit_error("Error on reading input");

	lexer = asm_init_lexer(input);
	parser = asm_init_parser(&lexer);
	if (!asm_parse(&tree, &parser))
		asm_exit_error(NULL);

	if (strcmp(argv[1], "--dot") == 0)
		asm_write_ast_dot_to_file(argv[argc - 1], tree);

	// semantic analysis
	if (!asm_validate_ast(&data, tree))
		asm_exit_error(NULL);

	// code generation
	asm_generate_output(argv[argc - 1], &data, tree);

	free(input);
	//system("leaks asm");
	return (0);
}
