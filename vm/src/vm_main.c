#include "../inc/vm.h"

// Segfault when -n or -dump is the last argument.

// first we need to read the arguments. A function that counts the players and saves
// the data that other arguments may contain. The identification numbers can be reassigned with the flag -n.
// read_input
// 		if (-n save_player(next))
//		else (save_player[i++])
// what is the smallest data type a processor can actually save in a register and read?

/*
** Reading the arguments passed to the VM. -n flag is followed by a player number that is
** given to the player named in the following argument. If -n is not specified,
*/

void	vm_error(const char *message)
{
	print("%s", message);
	exit(0);
}

void	vm_parse_bytecode(t_arena *arena, int *player_number, char *name)
{
	if (arena && player_number && name)
		return ;
}

void	vm_create_player(t_arena *arena, int *player_number, char *name)
{
	t_player	player;

	if (arena->all_players[*player_number].number)
		*player_number += 1;
	if (*player_number > MAX_PLAYERS)
		vm_error("player_number is not within MAX_PLAYERS\n");
	mzero(&player, sizeof(t_player));
	player.number = *player_number;
	arena->all_players[*player_number - 1] = player;
	vm_parse_bytecode(arena, player_number, name);
	*player_number += 1;
}


// Is prog_name always the same as the .cor file name?

void	vm_read_input(t_arena *arena, int argc, char **argv)
{
	int i;
	int	set_number;

	i = 0;
	while(i < argc)
	{
		if (!s_cmp(argv[i], "-n"))
		{
			set_number = s_toi(argv[++i]);
			if (set_number <= 0 || set_number > MAX_PLAYERS)
				vm_error("Invalid value after -n flag\n");
			if (arena->all_players[set_number - 1].header.prog_name[0])
				vm_error("All champions must be given unique numbers\n");
			s_cpy(arena->all_players[set_number - 1].header.prog_name, argv[++i]);
			arena->all_players[set_number - 1].number = set_number;
		}
		else if (!s_cmp(argv[i], "-dump"))
		{
			arena->dump_nbr_cycles = s_toi(argv[++i]);
			if (!arena->dump_nbr_cycles)
				vm_error("Incorrect nbr_cycles input\n");
		}
		i++;
	}
}

void	vm_init(t_arena *arena, int argc, char **argv)
{
	int	i;
	int	player_number;

	i = 0;
	player_number = 1;
	vm_read_input(arena, argc, argv);
	while (i < argc)
	{
		if (!s_cmp(argv[i], "-n"))
			i += 3;
		else if (!s_cmp(argv[i], "-dump"))
			i += 2;
		else
			vm_create_player(arena, &player_number, argv[i++]);
	}
}

int main(int argc, char **argv)
{
	t_arena	arena;

	if (argc < 2)
	{
		print("usage: vm [player_count][.cor]\n");
		return (0);
	}
	mzero(&arena, sizeof(t_arena));
	vm_init(&arena, argc, argv);
	return (0);
}