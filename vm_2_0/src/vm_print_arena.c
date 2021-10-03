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
		if (i == 0)
			print("0x0000 : ");
		else if (i % VM_PRINT_ARENA_WIDTH == 0)
			print("%#06x : ", i);
		if (vm_is_process_pc(i, process_list) && arena.coloured_output)
			print("\x1b[31m%02x\x1b[0m", arena.mem[i]);
		else
			print("%02x", arena.mem[i]);
		i++;
		if (i % VM_PRINT_ARENA_WIDTH == 0 && i != 0)
			print(" \n");
		else
			print(" ");
	}
}
