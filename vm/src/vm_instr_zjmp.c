#include "vm.h"

// zjmp T_DIR
// If zf is true, jump T_DIR bytes in memory.

void	vm_instr_zjmp(
		t_arena *a,
		t_process *p)
{
	t_argument	arg;
	t_size		jump;

	arg.size = DIR_VAL_SIZE;
	arg.type = T_DIR;
	jump = p->pc + 1;
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "zjmp offset");
	if (!p->zf)
		jump = DIR_VAL_SIZE;
	else
		jump = vm_get_val(a, p, arg, &jump) % IDX_MOD;
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\tmove pc to pc + %d\n", (int)jump);
	if ((a->verbosity & VM_VERBOSE_PC) != 0)
		print("\tPC: %d => %d\n", (int)p->pc, (p->pc + jump) % MEM_SIZE);
	p->pc = (p->pc + jump) % MEM_SIZE;
}
