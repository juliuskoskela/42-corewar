/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:20 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:21 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_process(t_process *p)
{
	t_size	i;

	print("id: %d pc: %d zf: %d\n", (int)p->id, (int)p->pc, (int)p->zf);
	print("last live: %d\n", (int)p->last_live);
	print("cycles before exec: %d\n", (int)p->cycles_before_execution);
	if (p->current_instruction.op != NULL)
		print("current instruction: %s\n", p->current_instruction.op->mnemonic);
	i = 0;
	while (i < 16)
	{
		print("R%d\t", i + 1);
		vm_reg_print(&p->registers[i]);
		print("\n");
		i++;
	}
}
