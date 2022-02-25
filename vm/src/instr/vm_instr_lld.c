/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_lld.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:14:54 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:14:54 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		3 (0x03)
/// mnemonic:	lld
/// name:		long load
/// params:		2 : { T_DIR | T_IND, T_REG }
/// acb:		true
/// ncycles:	10
/// proto:		lld src, dst
/// descript:	Long version of ld. Loads src in register dst,
///				value of src affects zf

#include "vm.h"

static void	load_indirect_value(t_arena *a, t_process *p, t_int8 dst_reg_addr)
{
	t_int16	offset;

	vm_reg_store((t_byte *)&offset, &p->current_instruction.args[0].data);
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => from pc + %d\n", offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + offset));
	vm_mem_read((t_byte *)&p->registers[dst_reg_addr - 1], &a->mem, REG_SIZE);
}

static void	load_direct_value(t_process *p, t_int8 dst_reg_addr)
{
	vm_reg_copy(&p->registers[dst_reg_addr - 1],
		&p->current_instruction.args[0].data);
}

void	vm_instr_lld(t_arena *a, t_process *p)
{
	t_int8	dst_reg_addr;

	vm_reg_store((t_byte *)&dst_reg_addr, &p->current_instruction.args[1].data);
	if (dst_reg_addr <= 0 || dst_reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (p->current_instruction.args[0].type == DIR_CODE)
		load_direct_value(p, dst_reg_addr);
	else
		load_indirect_value(a, p, dst_reg_addr);
	// zf !!!
	if (a->verbosity & VM_VERBOSE_OPS)
		vm_instr_print_register(" => load to R%d", dst_reg_addr, p);
}
