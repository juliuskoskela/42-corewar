/// opcode:		6 (0x06)
/// mnemonic:	and
/// name:		and
/// params:		3 : { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG }
/// acb:		true
/// ncycles:	6
/// proto:		and lhs, rhs, dst
/// descript:	Computes lhs & rhs and and stores the result in register dst.
///				Result affects zf.

#include "vm.h"

void	vm_instr_and(t_arena *a, t_process *p)
{
	t_int32	lhs;
	t_int32	rhs;
	t_int32	result;
	t_int8	reg_addr;

	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);
	if (reg_addr <= 0 || reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return ;
	}
	if (!vm_instr_get_param_value(&lhs, a, p, 0))
		return ;
	if (!vm_instr_get_param_value(&rhs, a, p, 1))
		return ;
	result = lhs & rhs;
	p->zf = (result == 0);
	vm_reg_load(&p->registers[reg_addr - 1], (t_byte *)&result);
	if (a->verbosity & VM_VERBOSE_OPS)
	{
		print(" => %d & %d = %d to R%d\n", lhs, rhs, result, reg_addr);
		vm_reg_print(&p->registers[reg_addr - 1]);
		print("\n");
	}
}
