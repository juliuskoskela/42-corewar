#include "asm.h"
#include "ast.h"
#include "generate.h"

static void	asm_resolve_label_forward_refs(t_output_data *data,
t_symbol_list *label)
{
	t_refnode	*ref_node;
	t_refnode	*next;
	int32_t		value;

	ref_node = label->forward_refs;
	while (ref_node != NULL)
	{
		value = label->node->num_value - (int32_t)ref_node->op_location;
		if (data->verbose)
		{
			asm_print_output_info("resolve forward reference for label",
				label->symbol, value);
		}
		asm_write_bytes(data, &ref_node->ref_location, &value, ref_node->size);
		next = ref_node->next;
		free(ref_node);
		ref_node = next;
	}
}

void	asm_resolve_label_address(t_output_data *data, uint32_t lc,
t_symbol_list **labels)
{
	t_symbol_list	*label;

	while (*labels != NULL)
	{
		label = asm_symbol_list_lookup(&data->symbols, (*labels)->symbol);
		if (data->verbose)
		{
			asm_print_output_info("save address for label",
				label->symbol, (int32_t)lc);
		}
		label->node->num_value = (int32_t)lc;
		asm_resolve_label_forward_refs(data, label);
		asm_symbol_list_delete(labels, (*labels)->symbol);
	}
}
