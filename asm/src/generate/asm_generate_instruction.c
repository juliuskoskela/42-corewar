/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "ast.h"
#include "generate.h"

void	asm_generate_instruction(t_output_data *data, t_location_counters *lc,
t_symbol_list **labels, t_astnode *node)
{
	t_op		instruction;

	if (data->verbose)
	{
		asm_print_output_info("\nGenerate instruction",
			node->value, (int32_t)(lc->current));
	}
	lc->current_op = lc->current;
	if (*labels != NULL)
		asm_resolve_label_address(data, lc->current_op, labels);
	asm_get_instruction(&instruction, node->value);
	if (data->verbose)
		asm_print_output_info("write opcode", NULL, instruction.opcode);
	asm_write_bytes(data, &lc->current, &instruction.opcode, 1);
	if (instruction.has_argument_coding_byte)
		asm_write_argument_coding_byte(data, &lc->current, node->right_child);
	else if (data->verbose)
		print("no argument coding byte\n");
	asm_write_arguments(data, lc, node);
}
