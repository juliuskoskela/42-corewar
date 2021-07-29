#include "ast.h"
#include <stdio.h>

static void	print_node(int fd, int nbr, const char *type, char *value)
{
	dprintf(fd, "node%d [label=<%s:%s>]\n", nbr, type, value);
}

static void	print_edge(int fd, int src_nbr, int dst_nbr)
{
	dprintf(fd, "node%d -> node%d\n", src_nbr, dst_nbr);
}

static int	print_subtree(int fd, t_astnode *node, int parent_nbr, int nbr)
{
	int	left_nbr;
	int	right_nbr;

	if (node->left_child != NULL)
	{
		left_nbr = ++nbr;
		print_node(fd, left_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(fd, parent_nbr, left_nbr);
	}
	if (node->right_child != NULL)
	{
		right_nbr = ++nbr;
		print_node(fd, right_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(fd, parent_nbr, right_nbr);
	}
	if (node->left_child != NULL)
		nbr = print_subtree(fd, node->left_child, left_nbr, nbr);
	if (node->right_child != NULL)
		nbr = print_subtree(fd, node->right_child, right_nbr, nbr);
	return (nbr);
}

static void	print_tree(int fd, t_astnode *node, int nbr)
{
	int	parent_nbr;
	int	left_nbr;
	int	right_nbr;

	if (node == NULL)
		return ;
	parent_nbr = nbr;
	print_node(fd, parent_nbr, g_astnode_types[node->type], node->value);
	if (node->left_child != NULL)
	{
		left_nbr = ++nbr;
		print_node(fd, left_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(fd, parent_nbr, left_nbr);
		nbr = print_subtree(fd, node->left_child, left_nbr, nbr);
	}
	if (node->right_child != NULL)
	{
		right_nbr = ++nbr;
		print_node(fd, right_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(fd, parent_nbr, right_nbr);
		nbr = print_subtree(fd, node->right_child, right_nbr, nbr);
	}
}

void	asm_print_ast_dot(int fd, t_astnode *root)
{
	dprintf(fd, "digraph astgraph {\
          node [shape=circle, fontsize=12, fontname=\"Courier\",height=.1];\
          ranksep=.3;\
          edge [arrowsize=.5]\n");
	print_tree(fd, root, 1);
	dprintf(fd, "}\n");
}

