#include "vm.h"

void vm_instr_alive(
		t_arena *a,
		t_process *p)
{
	t_argument	arg;
	t_process	*cur;
	t_size		mem_i;
	t_uint64	id;

	mem_i = p->pc;
	mem_i = (mem_i + 1) % MEM_SIZE;
	arg.size = REG_SIZE;
	arg.type = T_DIR;
	id = vm_get_val(a, p, arg, 1);
	cur = a->processes;
	while (cur && cur->id != id)
		cur = cur->next;
	if (!cur)
		vm_error("Process with id not found!\n");
	cur->last_live = a->cycles_executed;
	print("A process shows that player %d (%s) is alive\n", (int)cur->id, cur->header.prog_name);
	p->pc = mem_i;
}
