/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_lldi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:14:59 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:14:59 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// opcode:		14 (0x0e)
/// mnemonic:	lldi
/// name:		long load index
/// params:		3 : { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }
/// acb:		true
/// ncycles:	50
/// proto:		lldi lhs, rhs, dst
/// descript:	Computes lhs + rhs and uses the result as an offset to address
///				memory and load a 32-bit value from memory into the register
///				dst. In the long version of ldi, neither the parameter values
///				nor the computed address will have their reach limited.
///				Contrary to ldi, the value loaded from memory affects zf.

#include "vm.h"

void	vm_instr_lldi(t_arena *a, t_process *p)
{
	t_int32	lhs;
	t_int32	rhs;
	t_int32	offset;
	t_int8	dst_reg_addr;

	vm_reg_store((t_byte *)&dst_reg_addr, &p->current_instruction.args[2].data);
	if (dst_reg_addr <= 0 || dst_reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (!vm_instr_get_param_value(&lhs, a, p, 0))
		return ;
	if (!vm_instr_get_param_value(&rhs, a, p, 1))
		return ;
	offset = lhs + rhs;
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => from pc + (%d + %d = %d)\n", lhs, rhs, offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + offset));
	vm_mem_read((t_byte *)&p->registers[dst_reg_addr - 1], &a->mem, REG_SIZE);
	// zf !!!
	if (a->verbosity & VM_VERBOSE_OPS)
		vm_instr_print_register(" => load to R%d", dst_reg_addr, p);
}
