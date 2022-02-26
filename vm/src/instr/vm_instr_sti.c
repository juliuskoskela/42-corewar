/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_sti.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:15:21 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/26 13:28:56 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		11 (0x0b)
/// mnemonic:	sti
/// name:		store index
/// params:		3 : { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG }
/// acb:		true
/// ncycles:	25
/// proto:		sti src, lhs, rhs
/// descript:	Computes lhs + rhs and uses the result as an offset to address
///				memory and store the value of the register src at that memory
///				location.

#include "vm.h"

void	vm_instr_sti(t_arena *a, t_process *p)
{
	t_int8	src_reg_addr;
	t_int32	lhs;
	t_int32	rhs;
	t_int32	offset;

	vm_reg_store((t_byte *)&src_reg_addr, &p->current_instruction.args[0].data);
	if (src_reg_addr <= 0 || src_reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (!vm_instr_get_param_value(&lhs, a, p, 1))
		return ;
	if (!vm_instr_get_param_value(&rhs, a, p, 2))
		return ;
	offset = lhs + rhs;
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => store R%d in pc + (%d + %d = %d %% IDX_MOD)\n",
			src_reg_addr, lhs, rhs, offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + (offset % IDX_MOD)));
	vm_mem_write(&a->mem, (t_byte *)&p->registers[src_reg_addr - 1], REG_SIZE);
	if (a->verbosity & VM_VERBOSE_OPS)
		vm_instr_print_register(" => where R%d ", src_reg_addr, p);
}
