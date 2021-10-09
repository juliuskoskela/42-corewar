#include "vm.h"

void	vm_instr_fork(t_arena *a, t_process *p)
{
	t_int32     offset;
	t_process   *new;

	//Save first argument T_DIR value
	offset = vm_reg_deref(&offset, p->current_instr.args[0]);
	new = vm_create_process(a, p, p->id);
	//modify pc accordingly.
	new.pc = (p->pc + offset) % MEM_SIZE;
	//add new process to the end of the list
	while (p->next)
		p = p->next;
	p->next = new;
}