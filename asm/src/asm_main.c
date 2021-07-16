#include "asm.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char	*input;
	t_lexer	lexer;

	//parse flags
	if (argc != 2)
		asm_exit_error("Incorrect amount of arguments");

	//read input into string
	input = asm_read_input(argv[1]);
	if (input == NULL)
		asm_exit_error("Error on reading input");
	printf("'%s'\n", input);

	//initialize lexer
	lexer = asm_init_lexer(input);

	//parse
	asm_parse(&lexer);

	//semantic analysis
	//code generation
	free(input);
	//system("leaks asm");
	return (0);
}
