/// opcode:		3 (0x03)
/// mnemonic:	lld
/// name:		long load
/// params:		2 : { T_DIR | T_IND, T_REG }
/// acb:		true
/// ncycles:	10
/// proto:		lld src, dst
/// descript:	Long version of ld. Loads src in register dst, value of src affects zf

#include "vm.h"

void	vm_instr_lld(t_arena *a, t_process *p)
{
	t_int8	dst_reg_addr;
	t_int16	offset;

	vm_reg_store((t_byte *)&dst_reg_addr, &p->current_instruction.args[1].data);
	if (dst_reg_addr <= 0 || dst_reg_addr > 16)
	{
		print("invalid register address\n");
		return ;
	}
	if (p->current_instruction.args[0].type == DIR_CODE)
	{	
		vm_reg_copy(&p->registers[dst_reg_addr - 1], &p->current_instruction.args[0].data);
		//zf
	}
	else
	{
		vm_reg_store((t_byte *)&offset, &p->current_instruction.args[0].data);
		print(" => load value from pc + %d in R%d\n", offset, dst_reg_addr);
		if (offset % MEM_SIZE != 0) // ??
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + offset));
		vm_mem_read((t_byte *)&p->registers[dst_reg_addr - 1], &a->mem, REG_SIZE);
	}
	print(" => where R%d ", dst_reg_addr);
	vm_reg_print(&p->registers[dst_reg_addr - 1]);
	print("\n");
}
