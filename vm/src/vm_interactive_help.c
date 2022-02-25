#include "vm.h"

void	vm_interactive_print_processes(t_arena *arena, int arg)
{
	if (arg == 0 || arg > (int)arena->player_count)
		print("Invalid process id %d\n", arg);
	else
		vm_print_processes(arena, arg);
}

void	vm_interactive_print_arena(t_arena *arena, int arg)
{
	if (!arena || arg != -1)
		return ;
	vm_print_arena(*arena, arena->processes);
}

void	vm_interactive_exit(t_arena *arena, int arg)
{
	if (!arena || !arg)
		;
	exit(0);
}

void	vm_interactive_help(t_arena *arena, int arg)
{
	if (!arena || !arg)
		;
	print("Interactive options:\n\
	p [ID]\t\tprint all processes or processes related to an ID\n\
	a\t\tprint arena's memmory\n\
	exit\t\texit program\n\
	help\t\tprint this message\n\
	n [NBR]\t\tjump to the next cycle or NBR cycles forward\n");
}
