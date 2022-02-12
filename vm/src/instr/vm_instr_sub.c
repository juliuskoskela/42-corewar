/// opcode:		5 (0x05)
/// mnemonic:	sub
/// name:		substraction
/// params:		3 : { T_REG, T_REG, T_REG }
/// acb:		true
/// ncycles:	10
/// proto:		sub lhs, rhs, dst
/// descript:	Computes lhs - rhs and and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_sub(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate result(lhs - rhs)

	// Update zf

	// Store value to register dst
}
