#include "vm.h"

// Get the id for the new process from the first T_DIR argument.
// except the PC.

void	vm_instr_fork(
		t_arena *a,
		t_process *p)
)
{
	t_size		mem_i;
	t_uint64	id;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	id = vm_get_val(a, p, T_DIR, &mem_i);
	vm_create_process(a, a->processes, id]);
	a->process =
}