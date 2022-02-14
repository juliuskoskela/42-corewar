#include "vm.h"

// st ( dst, src )

void vm_print_process(t_process *p)
{
	t_size i;

	i = 0;
	while (i < 16)
	{
		vm_reg_print(&p->registers[i]);
		i++;
	}
}

void	vm_instr_st(t_arena *a, t_process *p)
{
	t_uint8		reg_addr;
	t_uint16	mem_addr;

	mem_addr = 0;
	// Get address of source register.
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[0].data);
	if (reg_addr > 16)
	{
		print("jadjsd\n");
		return ;
	}

	// If destination is a register, copy.
	if (p->current_instruction.args[1].type == REG_CODE)
	{
		print(" => Store R%u in R%u\n", reg_addr, p->current_instruction.args[0].data);
		vm_reg_copy(&p->registers[reg_addr - 1], &p->current_instruction.args[0].data);
	}
	else
	{
		vm_reg_store((t_byte *)&mem_addr, &p->current_instruction.args[1].data);
		print(" => Store R%u in %u\n", reg_addr, mem_addr);
		if (mem_addr % IDX_MOD != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, p->pc + mem_addr % IDX_MOD);
		vm_mem_write(&a->mem, (t_byte *)&p->registers[reg_addr - 1], REG_SIZE);
	}
	// print(" => %sR%d%s ", BLU, reg_addr, NRM);
	print(" => R%u ", reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	vm_print_process(p);
	return ;
}
