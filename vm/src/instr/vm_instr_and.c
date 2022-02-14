/// opcode:		6 (0x06)
/// mnemonic:	and
/// name:		and
/// params:		3 : { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG }
/// acb:		true
/// ncycles:	6
/// proto:		and lhs, rhs, dst
/// descript:	Computes lhs & rhs and and stores the result in register dst. Result affects zf.

#include "vm.h"

void	vm_instr_and(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate result(lhs & rhs)

	// Update zf

	// Store value to register dst
	vm_instr_null(a, p);
}
