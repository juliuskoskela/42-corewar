/// opcode:		14 (0x0e)
/// mnemonic:	lldi
/// name:		long load index
/// params:		3 : { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }
/// acb:		true
/// ncycles:	50
/// proto:		lldi lhs, rhs, dst
/// descript:	Computes lhs + rhs and uses the result as an offset to address memory and load a 32-bit value from memory into the register dst.
///				In the long version of ldi, neither the parameter values nor the computed address will have their reach limited. Contrary to ldi, the value loaded from memory affects zf.

#include "vm.h"

void	vm_instr_lldi(t_arena *a, t_process *p)
{
	// Get lhs, rhs

	// Calculate index (lhs + rhs) % IDX_MOD

	// Update zf

	// Store value at `index` to register dst
}