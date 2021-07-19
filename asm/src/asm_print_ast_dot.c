#include "ast.h"
#include <stdio.h>

void	print_node(int fd, int nbr, const char *type, char *value)
{
	dprintf(fd, "node%d [label=<%s:%s>]\n", nbr, type, value);
}

void	print_edge(int fd, int src_nbr, int dst_nbr)
{
	dprintf(fd, "node%d -> node%d\n", src_nbr, dst_nbr);
}

int	print_subtree(int fd, t_astnode *node, int parent_node_nbr, int node_nbr)
{
	int	left_node_nbr;
	int	right_node_nbr;

	if (node->left_child != NULL)
	{
		left_node_nbr = ++node_nbr;
		print_node(fd, left_node_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(fd, parent_node_nbr, left_node_nbr);
	}
	if (node->right_child != NULL)
	{
		right_node_nbr = ++node_nbr;
		print_node(fd, right_node_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(fd, parent_node_nbr, right_node_nbr);
	}
	if (node->left_child != NULL)
		node_nbr = print_subtree(fd, node->left_child, left_node_nbr, node_nbr);
	if (node->right_child != NULL)
		node_nbr = print_subtree(fd, node->right_child, right_node_nbr, node_nbr);
	return (node_nbr);
}

void	print_tree(int fd, t_astnode *node, int node_nbr)
{
	int	parent_node_nbr;
	int	left_node_nbr;
	int	right_node_nbr;

	if (node == NULL)
		return ;
	parent_node_nbr = node_nbr;
	print_node(fd, parent_node_nbr, g_astnode_types[node->type], node->value);
	if (node->left_child != NULL)
	{
		left_node_nbr = ++node_nbr;
		print_node(fd, left_node_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(fd, parent_node_nbr, left_node_nbr);
		node_nbr = print_subtree(fd, node->left_child, left_node_nbr, node_nbr);
	}
	if (node->right_child != NULL)
	{
		right_node_nbr = ++node_nbr;
		print_node(fd, right_node_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(fd, parent_node_nbr, right_node_nbr);
		node_nbr = print_subtree(fd, node->right_child, right_node_nbr, node_nbr);
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
