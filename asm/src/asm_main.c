#include "asm.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	asm_write_ast_dot_to_file(char *path, t_astnode *tree)
{
	char	*dot_file;
	size_t	path_len;
	size_t	file_name_len;
	int		fd;

	path_len = strlen(path);
	file_name_len = path_len + 2;
	dot_file = (char *)malloc(sizeof(char) * (file_name_len + 1));
	strcpy(dot_file, path);
	strcpy(&dot_file[path_len - 1], "dot");
	fd = open(dot_file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		asm_exit_error("Error on writing output to .dot file");
	printf("Writing AST to %s\n", dot_file);
	asm_print_ast_dot(fd, tree);
	close(fd);
}

int	main(int argc, char **argv)
{
	char		*input;
	t_lexer		lexer;
	t_parser	parser;
	t_astnode	*tree;

	if (argc < 2)
		asm_exit_error("Incorrect amount of arguments");

	input = asm_read_input(argv[argc - 1]);
	if (input == NULL)
		asm_exit_error("Error on reading input");

	lexer = asm_init_lexer(input);
	parser = asm_init_parser(&lexer);
	if (!asm_parse(&tree, &parser))
		asm_exit_error(NULL);

	// if --dot option is given,
	// print abstract syntax tree in dot syntax to a .dot file
	// to create an image, run
	// dot -Tpng -o filename.png filename.dot
	if (strcmp(argv[1], "--dot") == 0)
		asm_write_ast_dot_to_file(argv[argc - 1], tree);

	

	//semantic analysis

	//code generation

	free(input);
	//system("leaks asm");
	return (0);
}
