#include "vm.h"

void	vm_save_input(t_arena *arena, int argc, char **argv)
{
	t_input_args	args;
	int				i;

	args = vm_parse_arguments(argc, argv);
	arena->player_count = args.player_count;
	arena->offset = MEM_SIZE / (t_size)arena->player_count;
	arena->verbosity = args.verbosity;
	arena->dump_nbr_cycles = (t_size)args.dump_nbr_cycles;
	arena->pause_nbr_cycles = (t_size)args.pause_nbr_cycles;
	arena->interactive_mode = (t_bool)args.interactive_mode;
	i = 0;
	while (i < args.player_count)
	{
		vm_create_player(arena, &args.player_numbers[i], args.player_paths[i]);
		i++;
	}
	arena->last_player_alive = (t_size)arena->player_count;
}
