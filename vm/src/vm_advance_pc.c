#include "vm.h"

void	vm_advance_pc(t_size *pc, int size, t_byte *mem, int verbosity)
{
	t_size	new_pc;

	new_pc = (*pc + size) % MEM_SIZE;
	if ((verbosity & VM_VERBOSE_PC) != 0)
	{
		print("\t\tPC: %#06x => %#06x\t", (int)*pc, (int)new_pc);
		if (size > 0)
			vm_print_bytes(&mem[*pc], size);
		else
		{
			vm_print_bytes(&mem[*pc], MEM_SIZE - *pc);
			vm_print_bytes(&mem[0], size + *pc);
		}
		print("\n");
	}
	*pc = (*pc + size) % MEM_SIZE;
}
