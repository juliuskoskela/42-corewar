/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_instr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:29 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:30 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_instr(t_arena *a, t_process *p)
{
	t_size	i;

	vm_print_process_info(a, p);
	print("%s ( ", p->current_instruction.op->mnemonic);
	i = 0;
	while (i < p->current_instruction.op->param_count)
	{
		vm_print_instr_arg(&p->current_instruction.args[i]);
		if (i < p->current_instruction.op->param_count - 1)
			print(", ");
		i++;
	}
	print(" )\n");
}
