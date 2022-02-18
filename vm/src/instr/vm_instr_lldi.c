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
	t_int32 lhs;
	t_int32 rhs;
	t_int32 mem_addr;
	t_int32 reg_addr;

	// Get register
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);\

	if (reg_addr > 16)
	{
		print("reg addr > 16\n");
		return ;
	}

	// Get lhs, rhs
	vm_instr_get_param(&lhs, a, p, 0);
	vm_instr_get_param(&rhs, a, p, 1);

	// Calculate index lhs + rhs
	mem_addr = lhs + rhs;

	// Load value from `mem_addr` to register dst.
	vm_mem_set_pos(&a->mem, p->pc + mem_addr);
	vm_mem_read((t_byte *)&p->registers[reg_addr - 1], &a->mem, 4);
	
	//update zf
}