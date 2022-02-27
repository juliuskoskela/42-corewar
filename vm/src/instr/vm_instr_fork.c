/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:14:26 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/27 13:09:57 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		12 (0x0c)
/// mnemonic:	fork
/// name:		fork
/// params:		1 : { T_DIR }
/// acb:		false
/// ncycles:	800
/// proto:		fork offset
/// descript:	Forks this process: effectively creates a new process that
///				inherits the current process' registers and zf. The spawned
///				process has its PC set to his parent's PC offseted by offset.

#include "vm.h"

void	vm_instr_fork(t_arena *a, t_process *p)
{
	t_int16		offset;
	t_process	*new;

	vm_reg_store((t_byte *)&offset, &p->current_instruction.args[0].data);
	new = minit(sizeof(t_process));
	if (!new)
		vm_exit_error("Malloc fail\n");
	mcpy(new, p, sizeof(t_process));
	new->pc = (t_size)(((int)p->pc + (offset % IDX_MOD)) % MEM_SIZE);
	new->next = a->processes;
	new->id = a->processes->id + 1;
	new->cycles_before_execution = -1;
	mzero(&new->current_instruction, sizeof(t_instr));
	a->processes = new;
	if (a->verbosity & VM_VERBOSE_OPS)
	{
		print(" => old pc: %d offset: %d new pc: %d\n", p->pc, offset, new->pc);
		vm_test_fork(a->processes);
	}
}
