#include "vm.h"

void	vm_pause_and_print_memory(
		t_arena arena)
{
	char c;

	vm_print_arena(arena, arena.processes);
	read(1, &c, 1);
}