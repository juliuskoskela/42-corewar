/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_st.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:15:14 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:15:15 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		3 (0x03)
/// mnemonic:	st
/// name:		store
/// params:		2 : { T_REG, T_IND | T_REG }
/// acb:		true
/// ncycles:	5
/// proto:		st src, dst
/// descript:	Stores value of registry src in dst

#include "vm.h"

void	store_to_memory(t_arena *a, t_process *p, t_int8 src_reg_addr)
{
	t_int16	offset;

	vm_reg_store((t_byte *)&offset, &p->current_instruction.args[1].data);
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => store R%d in pc + (%d %% IDX_MOD)\n", src_reg_addr, offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + (offset % IDX_MOD)));
	vm_mem_write(&a->mem, (t_byte *)&p->registers[src_reg_addr - 1], REG_SIZE);
}

void	store_to_register(t_arena *a, t_process *p, t_int8 src_reg_addr)
{
	t_int8	dst_reg_addr;

	vm_reg_store((t_byte *)&dst_reg_addr, &p->current_instruction.args[1].data);
	if (dst_reg_addr <= 0 || dst_reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => store R%d in R%d\n", src_reg_addr, dst_reg_addr);
	vm_reg_copy(&p->registers[dst_reg_addr - 1],
		&p->registers[src_reg_addr - 1]);
}

void	vm_instr_st(t_arena *a, t_process *p)
{
	t_int8	src_reg_addr;

	vm_reg_store((t_byte *)&src_reg_addr, &p->current_instruction.args[0].data);
	if (src_reg_addr <= 0 || src_reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (p->current_instruction.args[1].type == REG_CODE)
		store_to_register(a, p, src_reg_addr);
	else
		store_to_memory(a, p, src_reg_addr);
	// zf !!!
	if (a->verbosity & VM_VERBOSE_OPS)
		vm_instr_print_register(" => where R%d", src_reg_addr, p);
}
