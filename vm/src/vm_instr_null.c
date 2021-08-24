#include "vm.h"

void vm_instr_null(
		t_arena *a,
		t_process *p)
{
	if ((a->verbosity & VM_VERBOSE_OPS) != 0)
		print("\t%s\n", "This instruction has not yet been implemented");
	a = NULL;
	p = NULL;
	if (a || p)
		return ;
	return ;
}
