#include "vm.h"

void	vm_init_arena(t_arena *arena)
{
	mzero(arena, sizeof(t_arena));
	arena->cycle_to_die = CYCLE_TO_DIE;
}

int	main(int argc, char **argv)
{
	t_arena	arena;

	// if (argc < 2)
	// {
	// 	print("usage: vm [player_count][.cor]\n");
	// 	return (0);
	// }
	vm_init_arena(&arena);
	vm_save_input(&arena, argc, argv);
	vm_test_print_arena(arena); //test
	vm_battle(arena);
	return (0);
}
