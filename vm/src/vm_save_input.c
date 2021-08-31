#include "vm.h"
#include "argparser.h"

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

static int	set_next_player_nbr(t_input_args *args)
{
	int	next_nbr;
	int	i;

	next_nbr = 1;
	i = 0;
	while (i < args->player_count)
	{
		if (next_nbr == args->player_numbers[i])
		{
			next_nbr += 1;
			i = 0;
		}
		else
			i++;
	}
	return (next_nbr);
}

static int	player_nbr_is_assigned(t_input_args *args, int nbr)
{
	int	i;

	i = 0;
	while (i < args->player_count)
	{
		if (args->player_numbers[i] == nbr)
			return (1);
		i++;
	}
	return (0);
}

static void	parse_numeric_option(int key, char *arg, t_argparser_state *state)
{
	t_input_args	*args;
	int				nbr;

	args = state->input;
	nbr = s_toi(arg);
	if (nbr == 0 && s_cmp(arg, "0") != 0)
		argparser_usage(state);
	else if (key == 'd' && nbr > 0)
		args->dump_nbr_cycles = nbr;
	else if (key == 'v' && (nbr >= 0 && nbr <= 31))
		args->verbosity = nbr;
	else if (key == 'n' && nbr > 0 && !player_nbr_is_assigned(args, nbr))
		args->next_player_nbr = nbr;
	else if (key == 's' && nbr > 0)
		args->pause_nbr_cycles = nbr;
	else
		argparser_usage(state);
}

static int	parse_opt(int key, char *arg, t_argparser_state *state)
{
	t_input_args	*args;

	args = state->input;
	if (key == 'd' || key == 'v' || key == 'n' || key == 's')
		parse_numeric_option(key, arg, state);
	else if (key == 'c')
		args->coloured_output = 1;
	else if (key == ARGP_KEY_ARG)
	{
		if (args->player_count == MAX_PLAYERS)
			argparser_usage(state);
		args->player_paths[args->player_count] = arg;
		args->player_numbers[args->player_count] = args->next_player_nbr;
		args->next_player_nbr = set_next_player_nbr(args);
		args->player_count += 1;
	}
	else if (key == ARGP_KEY_END)
	{
		if (args->player_count == 0)
			argparser_usage(state);
	}
	else
		return (ARGP_ERR_UNKNOWN);
	return (0);
}

t_input_args	vm_parse_arguments(int argc, char **argv)
{
	t_input_args					args;
	t_argparser						argparser;
	static const char				doc[] = "corewar: description";
	static const char				args_doc[] = "<path/to/player.cor> ...";
	static const t_argparser_option	options[] = {
		{"dump", 'd', "nbr_cycles", 0, "dump memory to standard output and exit\n\
				after nbr_cycles (> 0)"},
		{"show", 's', "nbr_cycles", 0, "dump memory every N cycles and pause until\n\
				a key is pressed"},
		{"verbosity", 'v', "level", 0, "verbosity level (set between 0 and 31)"},
		{"coloured", 'c', 0, 0, "use colours in printing to standard output"},
		{"nbr", 'n', "nbr", 0, "set the number (> 0) of the next player"},
		{0}
	};

	mzero(&args, sizeof(args));
	args.next_player_nbr = 1;
	mzero(&argparser, sizeof(argparser));
	argparser.doc = doc;
	argparser.args_doc = args_doc;
	argparser.options = options;
	argparser.parser = parse_opt;
	argparser_parse(&argparser, argc, argv, &args);
	return (args);
}

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
