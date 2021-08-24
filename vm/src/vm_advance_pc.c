#include "vm.h"

void	vm_advance_pc(t_size *pc, int size)
{
	*pc = (*pc + size) % MEM_SIZE;
}
