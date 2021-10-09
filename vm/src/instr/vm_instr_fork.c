#include "vm.h"

void	vm_instr_fork(t_arena *a, t_process *p)
{
	t_int32     offset;
	t_process   *new;

	//Save first argument T_DIR value
	vm_reg_deref((t_byte *)&offset, &p->current_instruction.args[0].data);
	new = vm_create_process(*a, p, p->id);
	//modify pc accordingly.
	new->pc = (p->pc + (offset % IDX_MOD)) % MEM_SIZE;
	//add new process to the end of the list
	while (p->next)
		p = p->next;
	p->next = new;
	print("fork"); //test
}