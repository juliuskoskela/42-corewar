#include "vm.h"

int	main(int argc, char **argv)
{
	t_arena	arena;

	if (argc < 2)
	{
		print("usage: vm [player_count][.cor]\n");
		return (0);
	}
	mzero(&arena, sizeof(t_arena));
	vm_save_input(&arena, argc, argv);
	vm_test_print_arena(arena);
	vm_battle(arena);
	return (0);
}
