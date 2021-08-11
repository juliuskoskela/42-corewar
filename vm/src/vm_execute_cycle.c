#include "vm.h"

void	vm_execute_lst(t_process *processes, t_battle *battle)
{
	while (processes)
	{
		//
		processes->cycles_before_execution--;
		processes = processes->next;
	}
}

t_uint32	vm_execute_cycle(t_process *processes, t_battle *battle)
{
	//execute each process
	vm_execute_list(processes, battle);
	battle->cycles_executed += 1;
}