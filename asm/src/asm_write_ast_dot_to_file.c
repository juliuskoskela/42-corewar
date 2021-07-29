#include "ast.h"
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
	free(dot_file);
	asm_print_ast_dot(fd, tree);
	close(fd);
}

