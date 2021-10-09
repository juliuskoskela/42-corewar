#include "vm.h"

void	vm_instr_fork(t_arena *a, t_process *p)
{
	t_int32     offset;
	t_process	*new;

	//Save first argument T_DIR value
	vm_reg_deref((t_byte *)&offset, &p->current_instruction.args[0].data);
	new = minit(sizeof(t_process));
	if (!new)
		vm_exit_error("Malloc fail\n");
	mcpy(new, p, sizeof(t_process));
	new->pc = (p->pc + (offset % IDX_MOD)) % MEM_SIZE;
	new->next = a->processes;
	a->processes = new;
	//vm_test_print_processes(a);
}