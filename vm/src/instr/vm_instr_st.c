/// opcode:		3 (0x03)
/// mnemonic:	st
/// name:		store
/// params:		2 : { T_REG, T_IND | T_REG }
/// acb:		true
/// ncycles:	5
/// proto:		st src, dst
/// descript:	Stores value of registry src in dst

#include "vm.h"

void	vm_instr_st(t_arena *a, t_process *p)
{
	t_uint8		src_reg_addr;
	t_uint8		dst_reg_addr;
	t_int16		mem_addr;

	vm_reg_store((t_byte *)&src_reg_addr, &p->current_instruction.args[0].data);
	if (src_reg_addr <= 0 || src_reg_addr > 16)
	{
		print("invalid reg_addr\n");
		return ;
	}
	if (p->current_instruction.args[1].type == REG_CODE)
	{
		vm_reg_store((t_byte *)&dst_reg_addr, &p->current_instruction.args[1].data);
		if (dst_reg_addr <= 0 || dst_reg_addr > 16)
		{
			print("invalid reg_addr\n");
			return ;
		}
		print(" => Store R%u in R%u\n", src_reg_addr, dst_reg_addr);
		vm_reg_copy(&p->registers[dst_reg_addr - 1], &p->registers[src_reg_addr - 1]);
	}
	else
	{
		vm_reg_store((t_byte *)&mem_addr, &p->current_instruction.args[1].data);
		print(" => Store R%u in pc + (%d %% IDX_MOD)\n", src_reg_addr, mem_addr);
		vm_mem_set_pos(&a->mem, p->pc + (mem_addr % IDX_MOD));
		vm_mem_write(&a->mem, (t_byte *)&p->registers[src_reg_addr - 1], REG_SIZE);
	}
	// print(" => %sR%d%s ", BLU, reg_addr, NRM);
	print(" => R%u ", src_reg_addr);
	vm_reg_print(&p->registers[src_reg_addr - 1]);
	print("\n");
	vm_print_process(p);
	return ;
}
