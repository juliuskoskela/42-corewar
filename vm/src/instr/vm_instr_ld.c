#include "vm.h"
// static void	vm_print_instr_ld(t_arena *a, t_process *p, const char *action)
// {
// 	t_size	i;

// 	vm_print_process_info(a, p);
// 	print("%s%s%s ", GRN, action, NRM);
// 	print("%s ( ", p->current_instruction.op->mnemonic);
// 	i = 0;
// 	while (i < p->current_instruction.op->param_count)
// 	{
// 		vm_print_instr_arg(&p->current_instruction.args[i]);
// 		if (i < p->current_instruction.op->param_count - 1)
// 			print(", ");
// 		i++;
// 	}
// 	print(" )");
// }

void	vm_instr_ld(t_arena *a, t_process *p)
{
	t_uint8		reg_addr;
	t_uint16	mem_addr;

	vm_reg_deref((t_byte *)&reg_addr, &p->current_instruction.args[1].data);
	if (reg_addr > 16)
		return ;
	if (p->current_instruction.args[0].type == DIR_CODE)
		vm_reg_copy(&p->registers[reg_addr - 1], &p->current_instruction.args[0].data);
	else
	{
		vm_reg_deref((t_byte *)&mem_addr, &p->current_instruction.args[0].data);
		if (mem_addr % IDX_MOD != 0)
			p->zf = TRUE;
		vm_mem_set_pos(&a->mem, (p->pc + mem_addr) % IDX_MOD);
		vm_mem_read((t_byte *)&p->registers[reg_addr - 1], &a->mem, 4);
	}
	print(" => %sR%d%s ", BLU, reg_addr, NRM);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
	return ;
}
