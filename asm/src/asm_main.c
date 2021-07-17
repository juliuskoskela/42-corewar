#include "asm.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char		*input;
	t_lexer		lexer;
	t_parser	parser;
	t_astnode	*tree;

	//parse flags
	if (argc != 2)
		asm_exit_error("Incorrect amount of arguments");

	//read input into string
	input = asm_read_input(argv[1]);
	if (input == NULL)
		asm_exit_error("Error on reading input");

	//initialize lexer
	lexer = asm_init_lexer(input);

	//initialize parser & parse
	parser = asm_init_parser(&lexer);
	tree = asm_parse(&parser);

	//print abstract syntax tree in dot syntax
	asm_print_ast_dot(tree);

	//semantic analysis

	//code generation

	free(input);
	//system("leaks asm");
	return (0);
}
