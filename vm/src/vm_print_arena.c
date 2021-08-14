#include "vm.h"

static int	vm_is_process_pc(t_uint32 address, t_process *process)
{
	while (process)
	{
		if (process->pc == address)
			return (1);
		process = process->next;
	}
	return (0);
}

void	vm_print_arena(t_arena arena, t_process *process_list)
{
	t_uint32	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm_is_process_pc(i, process_list))
			print("\x1b[31m%-2x\x1b[0m", arena.mem[i]);
		else
			print("%-2x", arena.mem[i]);
		i++;
		if (i % 32 == 0 && i != 0)
			print("\n");
		else
			print(" ");
	}
}
