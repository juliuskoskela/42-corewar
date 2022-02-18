/// opcode:		7 (0x07)
/// mnemonic:	or
/// name:		or
/// params:		3 : { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG }
/// acb:		true
/// ncycles:	6
/// proto:		or lhs, rhs, dst
/// descript:	Computes (lhs | rhs) and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_or(t_arena *a, t_process *p)
{
	t_int32	lhs;
	t_int32	rhs;
	t_int32	result;
	t_uint8	reg_addr;

	// Get lhs, rhs
	if (!vm_instr_get_param(&lhs, a, p, 0))
		return ;
	if (!vm_instr_get_param(&rhs, a, p, 1))
		return ;

	// Calculate result(lhs | rhs)
	result = lhs | rhs;
	//print result
	print("lhs | rhs = %d | %d = %d\n", lhs, rhs, (int)result);

	// Update zf
	p->zf = (result == 0);

	// Get result register address
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);
	//print dst reg_addr
	print("dst reg addr: %d\n", (int)reg_addr);
	if (reg_addr > 16)
		return ;

	// Store result in register
	vm_reg_load(&p->registers[reg_addr - 1], (t_byte *)&result);
	// print reg contents
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
}
