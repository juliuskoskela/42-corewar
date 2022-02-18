/// opcode:		11 (0x0b)
/// mnemonic:	sti
/// name:		store index
/// params:		3 : { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG }
/// acb:		true
/// ncycles:	25
/// proto:		sti src, lhs, rhs
/// descript:	Computes lhs + rhs and uses the result as an offset to address memory and store the value of the register src at that memory location.

#include "vm.h"

void	vm_instr_sti(t_arena *a, t_process *p)
{
	t_uint8	reg_addr;
	t_int32	lhs;
	t_int32	rhs;
	t_int32	mem_offset;

	// Get lhs, rhs
	if (!vm_instr_get_param(&lhs, a, p, 0))
		return ;
	if (!vm_instr_get_param(&rhs, a, p, 1))
		return ;

	// Calculate offset (lhs + rhs)
	mem_offset = lhs + rhs;
	print("lhs + rhs = %d + %d = %d\n", lhs, rhs, (int)mem_offset);

	// Get src register address
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);
	print("src reg addr: %d\n", (int)reg_addr);
	if (reg_addr > 16)
		return ;
	vm_reg_print(&p->registers[reg_addr - 1]);

	// Store register src in memory
	vm_mem_set_pos(&a->mem, p->pc + mem_offset % IDX_MOD);
	vm_mem_write(&a->mem, (t_byte *)&p->registers[reg_addr - 1], REG_SIZE);
}
