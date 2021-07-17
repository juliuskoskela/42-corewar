#include "ast.h"
#include <stdio.h>

void	print_node(int nbr, const char *type, char *value)
{
	printf("node%d [label=<%s:%s>]\n", nbr, type, value);
}

void	print_edge(int src_nbr, int dst_nbr)
{
	printf("node%d -> node%d\n", src_nbr, dst_nbr);
}

int	print_subtree(t_astnode *node, int parent_node_nbr, int node_nbr)
{
	int	left_node_nbr;
	int	right_node_nbr;

	if (node->left_child != NULL)
	{
		left_node_nbr = ++node_nbr;
		print_node(left_node_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(parent_node_nbr, left_node_nbr);
	}
	if (node->right_child != NULL)
	{
		right_node_nbr = ++node_nbr;
		print_node(right_node_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(parent_node_nbr, right_node_nbr);
	}
	if (node->left_child != NULL)
		node_nbr = print_subtree(node->left_child, left_node_nbr, node_nbr);
	if (node->right_child != NULL)
		node_nbr = print_subtree(node->right_child, right_node_nbr, node_nbr);
	return (node_nbr);
}

void	print_tree(t_astnode *node, int node_nbr)
{
	int	parent_node_nbr;
	int	left_node_nbr;
	int	right_node_nbr;

	if (node == NULL)
		return ;
	parent_node_nbr = node_nbr;
	print_node(parent_node_nbr, g_astnode_types[node->type], node->value);
	if (node->left_child != NULL)
	{
		left_node_nbr = ++node_nbr;
		print_node(left_node_nbr, g_astnode_types[node->left_child->type],
			node->left_child->value);
		print_edge(parent_node_nbr, left_node_nbr);
		node_nbr = print_subtree(node->left_child, left_node_nbr, node_nbr);
	}
	if (node->right_child != NULL)
	{
		right_node_nbr = ++node_nbr;
		print_node(right_node_nbr, g_astnode_types[node->right_child->type],
			node->right_child->value);
		print_edge(parent_node_nbr, right_node_nbr);
		node_nbr = print_subtree(node->right_child, right_node_nbr, node_nbr);
	}
}

void	asm_print_ast_dot(t_astnode *root)
{
	printf("digraph astgraph {\
          node [shape=circle, fontsize=12, fontname=\"Courier\",height=.1];\
          ranksep=.3;\
          edge [arrowsize=.5]\n");
	print_tree(root, 1);
	printf("}\n");
}
