#include "vm.h"

void	vm_increment_process_pc(t_process *p, t_int32 delta, t_int32 verbosity)
{
	t_size	new_pc;

	new_pc = (t_size)((int)p->pc + delta) % MEM_SIZE;
	if (verbosity & VM_VERBOSE_PC)
	{
		print(" => pc: %d (%#06x) => %d (%#06x) \n",
			p->pc, p->pc, new_pc, new_pc);
	}
	p->pc = new_pc;
}
