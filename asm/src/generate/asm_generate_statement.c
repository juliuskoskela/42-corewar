#include "asm.h"
#include "ast.h"
#include "generate.h"

static int	asm_add_label_to_list(t_symbol_list **labels, t_astnode *label)
{
	t_symbol_list	*node;

	if (*labels == NULL)
		*labels = asm_symbol_list_new(label, label->value);
	else
	{
		node = *labels;
		while (node->next != NULL)
			node = node->next;
		node->next = asm_symbol_list_new(label, label->value);
	}
	return (1);
}

int	asm_generate_statement(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	if (node->left_child != NULL)
		asm_add_label_to_list(labels, node->left_child);
	if (node->right_child != NULL && node->right_child->type == INSTRUCTION)
		return (asm_generate_instruction(data, lc, labels, node->right_child));
	return (1);
}
