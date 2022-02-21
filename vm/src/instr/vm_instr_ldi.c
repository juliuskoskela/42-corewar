/// opcode:		10 (0x0a)
/// mnemonic:	ldi
/// name:		load index
/// params:		3 : { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }
/// acb:		true
/// ncycles:	25
/// proto:		ldi lhs, rhs, dst
/// descript:	Computes lhs + rhs and uses the result as an offset to address
///				memory and load a 32-bit value from memory into the register
///				dst.

#include "vm.h"

void	vm_instr_ldi(t_arena *a, t_process *p)
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
		print(" => from pc + (%d + %d = %d %% IDX_MOD)\n", lhs, rhs, offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + (offset % IDX_MOD)));
	vm_mem_read((t_byte *)&p->registers[dst_reg_addr - 1], &a->mem, REG_SIZE);
	// zf !!!
	if (a->verbosity & VM_VERBOSE_OPS)
		vm_instr_print_register(" => load to R%d", dst_reg_addr, p);
}
