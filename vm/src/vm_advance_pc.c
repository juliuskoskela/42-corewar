#include "vm.h"

void	vm_advance_pc(t_size *pc, int size, int verbosity)
{
	t_size	new_pc;

	new_pc = (*pc + size) % MEM_SIZE;
	if ((verbosity & VM_VERBOSE_PC) != 0)
		print("\t\tPC: %d => %d\n", (int)*pc, (int)new_pc);
	*pc = (*pc + size) % MEM_SIZE;
}
