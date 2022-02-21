#include "vm.h"

void	vm_print_processes(t_arena *a, int id)
{
	t_bool		found_live_processes;
	t_process	*p;

	found_live_processes = 0;
	p = a->processes;
	print("printing processes:\n");
	while (p)
	{
		if (id == -1 || p->id == (t_uint32)id)
		{
			vm_print_process(p);
			print("\n");
			found_live_processes = 1;
		}
		p = p->next;
	}
	if (!found_live_processes)
		print("no live processes\n");
}
