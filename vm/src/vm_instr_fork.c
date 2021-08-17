#include "vm.h"

// Get the id for the new process from the first T_DIR argument.
// Copy the memory of the current process.
// Modify the pc of the new process.

void	vm_instr_fork(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint64	id;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	id = vm_get_val(a, p, T_DIR, &mem_i);
	vm_create_process(*a, a->processes, p->id);
	mcpy(a->processes, p, sizeof(t_process));
	a->processes->pc = p->pc + (id % IDX_MOD);
}