/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_zjmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:15:34 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:15:35 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		9 (0x09)
/// mnemonic:	zjmp
/// name:		jump if zero
/// params:		1 : { T_DIR }
/// acb:		false
/// ncycles:	20
/// proto:		zjmp offset
/// descript:	Moves the process's PC by offset only if
///				the process's zf is set to 1.

#include "vm.h"

void	vm_instr_zjmp(t_arena *a, t_process *p)
{
	t_int32	offset;

	vm_reg_store((t_byte *)&offset, &p->current_instruction.args[0].data);
	if (p->zf)
	{
		p->pc = (t_size)((int)p->pc + (offset % IDX_MOD)) % MEM_SIZE;
		if (a->verbosity & VM_VERBOSE_OPS)
			print(" => pc jump to %d\n", p->pc);
	}
	else
	{
		vm_process_debug(" => zf is not set", a->verbosity);
	}
}
