#include "vm.h"

// aff T_DIR
// If zf is true, jump T_DIR bytes in memory.

void	vm_instr_zjmp(
		t_arena *a,
		t_process *p)
{
	t_size	jump;

	if (!p->zf)
		jump = DIR_VAL_SIZE + 1;
	else
	{
		jump = (p->pc + 1) % MEM_SIZE;
		jump = vm_get_val(a, p, DIR_CODE, &jump) % IDX_MOD;
	}
	p->pc = (p->pc + jump) % MEM_SIZE;
}