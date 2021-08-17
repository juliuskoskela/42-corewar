#include "vm.h"

void vm_instr_null(
		t_arena *a,
		t_process *p)
{
	a = NULL;
	p = NULL;
	if (a || p)
		return ;
	return ;
}