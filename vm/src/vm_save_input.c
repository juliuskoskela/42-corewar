#include "vm.h"

// /*
// ** Skips flags (-n and -dump) and their following argument.
// ** other args are counted as players.
// */

// static t_uint32	vm_count_players(t_uint32 argc, char **argv)
// {
// 	t_uint32	i;
// 	t_uint32	player_count;

// 	i = 0;
// 	player_count = 0;
// 	while (++i < argc)
// 	{
// 		if (s_cmp(argv[i], "-n") && s_cmp(argv[i], "-dump") && s_cmp(argv[i], "-v"))
// 			player_count++;
// 		else
// 			i++;
// 	}
// 	return (player_count);
// }

// /*
// **	Checking that the args given to the vm are valid. The players that
// **	get id nbrs assigned by the -n flag are saved to the arena at this
// **	stage. -n and -dump flags must be followed by a numeric argument.
// */

// static void	vm_validate_input(t_arena *arena, t_uint32 argc, char **argv)
// {
// 	t_uint32	i;
// 	t_int32		set_nbr;

// 	i = 0;
// 	while (++i < argc)
// 	{
// 		if (argv[i][0] == '-' && i + 1 == argc)
// 			vm_error("No argument after -flag\n");
// 		if (!s_cmp(argv[i], "-n"))
// 		{
// 			set_nbr = s_toi(argv[++i]);
// 			if (set_nbr <= 0 || set_nbr > MAX_PLAYERS)
// 				vm_error("Invalid value after -n flag\n");
// 			if (arena->all_players[set_nbr - 1].prog_size ||
// 			arena->all_players[set_nbr - 1].prog_name[0])
// 				vm_error("All champions must be given unique nbrs\n");
// 			vm_create_player(arena, &set_nbr, argv[++i]);
// 		}
// 		else if (!s_cmp(argv[i], "-v"))
// 		{
// 			set_nbr = s_toi(argv[++i]);
// 			if (set_nbr < 0 || (set_nbr == 0 && argv[i][0] != '0'))
// 				vm_error("Invalid value after -v flag\n");
// 			arena->verbosity = set_nbr;
// 		}
// 		else if (!s_cmp(argv[i], "-dump"))
// 		{
// 			arena->dump_nbr_cycles = s_toi(argv[++i]);
// 			if (arena->dump_nbr_cycles <= 0)
// 				vm_error("Invalid value after -dump\n");
// 		}
// 	}
// }

// /*
// ** vm_validate_input checks the args -n and -dump. In this loop flags and
// ** their args are skipped. Players are saved in argument order to the first
// ** available spot in arena->all_players. Player nbrs can be assigned with the
// ** -n flag.
// */

// void	vm_save_input(t_arena *arena, t_uint32 argc, char **argv)
// {
// 	t_uint32	i;
// 	t_int32		player_nbr;

// 	i = 1;
// 	player_nbr = 1;
// 	vm_validate_input(arena, argc, argv);
// 	arena->player_count = vm_count_players(argc, argv);
// 	arena->offset = MEM_SIZE / arena->player_count;
// 	while (i < argc)
// 	{
// 		if (!s_cmp(argv[i], "-n") || !s_cmp(argv[i], "-v"))
// 			i += 3;
// 		else if (!s_cmp(argv[i], "-dump"))
// 			i += 2;
// 		else
// 			vm_create_player(arena, &player_nbr, argv[i++]);
// 	}
// }

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
	i = 0;
	while (i < args.player_count)
	{
		vm_create_player(arena, &args.player_numbers[i], args.player_paths[i]);
		i++;
	}
}
