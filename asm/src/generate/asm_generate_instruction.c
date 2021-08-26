#include "asm.h"
#include "ast.h"
#include "generate.h"

void	asm_generate_instruction(t_output_data *data, uint32_t *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_op		instruction;
	uint32_t	current_op_lc;

	if (data->verbose)
	{
		asm_print_output_info("\nGenerate instruction",
			node->value, (int32_t)(*lc));
	}
	current_op_lc = *lc;
	if (*labels != NULL)
		asm_resolve_label_address(data, current_op_lc, labels);
	asm_get_instruction(&instruction, node->value);
	if (data->verbose)
		asm_print_output_info("write opcode", NULL, instruction.opcode);
	asm_write_bytes(data, lc, &instruction.opcode, 1);
	if (instruction.has_argument_coding_byte)
		asm_write_argument_coding_byte(data, lc, node->right_child);
	else if (data->verbose)
		print("no argument coding byte\n");
	asm_write_arguments(data, lc, current_op_lc, node);
}
