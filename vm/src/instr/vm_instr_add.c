/// opcode:		4 (0x04)
/// mnemonic:	add
/// name:		addition
/// params:		3 : { T_REG, T_REG, T_REG }
/// acb:		true
/// ncycles:	10
/// proto:		add lhs, rhs, dst
/// descript:	Computes lhs + rhs and and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_add(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate result(lhs + rhs)

	// Update zf

	// Store value to register dst
}
