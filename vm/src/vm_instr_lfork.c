#include "vm.h"

// Takes one argument of type T_DIR.
//
// Copy the memory of the current process.
// Set the PC at PC + 1st_parameter.

void	vm_instr_lfork(
		t_arena *a,
		t_process *p)
{
	t_size		mem_i;
	t_int64		offset;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "lfork offset");
	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	offset = vm_get_val(a, p, T_DIR, &mem_i);
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "fork to pc + %d\n", (int)offset);
	vm_create_process(*a, a->processes, p->id);
	mcpy(a->processes, p, sizeof(t_process));
	a->processes->pc = (p->pc + offset) % MEM_SIZE;
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (int)mem_i);
	p->pc = mem_i;
}
