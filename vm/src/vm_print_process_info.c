#include "vm.h"

void	vm_print_process_info(t_arena *a, t_process *p)
{
	print("[%#06llu][%#06llu][%#06llu] ", a->current_cycle, p->id, p->pc);
}
