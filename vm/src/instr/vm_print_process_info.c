#include "instr.h"

void	vm_print_process_info(t_arena *a, t_process *p)
{
	print("[%#08llu][%#08llu][%#08llu] ", a->current_cycle, p->id, p->pc);
}
