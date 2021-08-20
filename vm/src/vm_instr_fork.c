#include "vm.h"

// Takes one argument of type T_DIR.
//
// Copy the memory of the current process.
// Set the PC at (PC + (1st parameter % IDX_MOD)).

void	vm_instr_fork(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_uint64	offset;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	offset = vm_get_val(a, p, T_DIR, &mem_i);
	vm_create_process(*a, a->processes, p->id);
	mcpy(a->processes, p, sizeof(t_process));
	a->processes->pc = p->pc + (offset % IDX_MOD);
	p->pc =+ DIR_VAL_SIZE % MEM_SIZE;
}