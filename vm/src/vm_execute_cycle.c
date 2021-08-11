#include "vm.h"

void	vm_execute_lst(t_process *processes, t_battle *battle)
{
	while (processes && battle)
	{
		processes->cycles_before_execution--;
		processes = processes->next;
	}
}

void	vm_execute_cycle(t_process *processes, t_battle *battle)
{
	vm_execute_lst(processes, battle);
	battle->cycles_executed += 1;
}
