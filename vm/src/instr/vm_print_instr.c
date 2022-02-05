#include "vm.h"

void	vm_print_instr(t_arena *a, t_process *p)
{
	t_size	i;

	vm_print_process_info(a, p);
	print("%s%s%s ( ", GRN, p->current_instruction.op->mnemonic, NRM);
	i = 0;
	while (i < p->current_instruction.op->param_count)
	{
		vm_print_instr_arg(&p->current_instruction.args[i]);
		if (i < p->current_instruction.op->param_count - 1)
			print(", ");
		i++;
	}
	print(" )");
}
