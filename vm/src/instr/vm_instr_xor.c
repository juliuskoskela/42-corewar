/// opcode:		8 (0x08)
/// mnemonic:	xor
/// name:		xor
/// params:		3 : { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG }
/// acb:		true
/// ncycles:	6
/// proto:		xor lhs, rhs, dst
/// descript:	Computes (lhs ^ rhs) and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_xor(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate result(lhs ^ rhs)

	// Update zf

	// Store value to register dst
}
