#include "asm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

static void	asm_astnode_free(t_astnode *tree)
{
	if (tree->left_child != NULL)
		asm_astnode_free(tree->left_child);
	if (tree->right_child != NULL)
		asm_astnode_free(tree->right_child);
	free(tree->token.value);
	free(tree);
}

static void	asm_symbol_list_free(t_symbol_list list)
{
	t_symbol_list	*node;
	t_symbol_list	*next;

	node = list.next;
	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

static void	asm_print_usage(void)
{
	static const char	*usage = "Usage: ./asm [--dot] path/to/player.s\n\
	\n\
	--dot: write the intermediate abstract syntax tree to path/to/player.dot\n\
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
	tree = NULL;
	if (!asm_parse(&tree, &parser))
		asm_exit_error(NULL);

	if (strcmp(argv[1], "--dot") == 0)
		asm_write_ast_dot_to_file(argv[argc - 1], tree);

	asm_init_output_data(&data);
	if (!asm_validate_ast(&data, tree))
		asm_exit_error(NULL);

	asm_generate_output(argv[argc - 1], &data, tree);

	asm_astnode_free(tree);
	asm_symbol_list_free(data.symbols);
	free(input);
	return (0);
}
