#include "vm.h"

void	vm_init_arena(t_arena *arena)
{
	mzero(arena, sizeof(t_arena));
	if (vm_mem_new(&arena->mem, MEM_SIZE) == NULL)
		vm_exit_error("failed to allocate memory");
	arena->cycle_to_die = CYCLE_TO_DIE;
	arena->current_cycle = 1;
}

void	vm_free_arena_memory(t_arena *arena)
{
	vm_mem_free(&arena->mem);
}

int	main(int argc, char **argv)
{
	t_arena	arena;

	vm_init_arena(&arena);
	vm_save_input(&arena, argc, argv);
	vm_battle(arena);
	vm_free_arena_memory(&arena);
	return (0);
}
