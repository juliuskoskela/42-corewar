#include "vm.h"

// zjmp T_DIR
// If zf is true, jump T_DIR bytes in memory.

void	vm_instr_zjmp(
		t_arena *a,
		t_process *p)
{
	t_size	jump;

	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "zjmp offset");
	if (!p->zf)
		jump = DIR_VAL_SIZE + 1;
	else
	{
		jump = (p->pc + 1) % MEM_SIZE;
		jump = vm_get_val(a, p, DIR_CODE, &jump) % IDX_MOD;
	}
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\tmove pc to pc + %d\n", (int)jump);
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (p->pc + jump) % MEM_SIZE);
	p->pc = (p->pc + jump) % MEM_SIZE;
}
