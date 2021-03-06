#include "vm.h"

void	vm_save_input(t_arena *arena, t_uint32 argc, char **argv)
{
	t_input_args	args;
	int				i;

	args = vm_parse_arguments(argc, argv);
	arena->player_count = args.player_count;
	arena->offset = MEM_SIZE / arena->player_count;
	arena->verbosity = args.verbosity;
	arena->dump_nbr_cycles = args.dump_nbr_cycles;
	arena->pause_nbr_cycles = args.pause_nbr_cycles;
	arena->interactive_mode = args.interactive_mode;
	i = 0;
	while (i < args.player_count)
	{
		vm_create_player(arena, &args.player_numbers[i], args.player_paths[i]);
		i++;
	}
}
