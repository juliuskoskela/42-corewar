#include "../inc/vm.h"

t_bool	vm_init_player(
		t_arena *arena,
		t_player *player,
		t_instructions *instr,
		t_size id)
{
	player = malloc(sizeof(t_player));
	if (!player)
		return (FALSE);
	mzero(player, sizeof(t_player));
	player->id = id;
	player->pc = &arena->mem[arena->offset];
	player->zf = 0;
	player->r1 = player->id;
	// Copy player instructions to shared memory.
	mcpy(player->pc, instr->bytes, instr->size * sizeof(t_byte));
	return (TRUE);
}

t_bool	vm_get_instructions(
		t_instructions *instr,
		char *filename)
{
	// Read instructions from file.
	t_parray	file;

	file = parr_new(1);
	if (!(parr_read_file(&file, filename)))
	{
		print("Error reading file.\n");
		parr_free(&file);
		return (FALSE);
	}

	// Parse instructions from file to instr->mem.
	// File is an array of string lines.
	instr = NULL;
	instr->size = 0;
	// Free page.
	parr_free(&file);
	return (TRUE);
}

void	vm_free_instr(t_instructions *instr)
{
	free(instr->bytes);
	instr->bytes = 0;
}

t_bool	vm_init_arena(t_arena *arena, t_size argc, char **argv)
{
	t_instructions	instr;
	t_uint32		i;

	mzero(arena->mem, sizeof(t_byte) * MEM_SIZE);
	arena->player_count = s_toi(argv[1]);
	if (argc - 2 != arena->player_count)
	{
		print("Player count doesn't match with input files!\n");
		exit(-1);
	}
	arena->offset = MEM_SIZE / arena->player_count;
	arena->all_players = malloc(sizeof(t_player *) * arena->player_count);
	i = 2;
	while (i < arena->player_count)
	{
		if (!(vm_get_instructions(&instr, argv[i])))
			return (FALSE);
		if (!(vm_init_player(arena, &arena->all_players[i], &instr, i)))
			return (FALSE);
		vm_free_instr(&instr);
		i++;
	}
	return (TRUE);
}

void	vm_free_arena(t_arena *arena)
{
	t_size	i;

	i = 0;
	while (i < arena->player_count)
	{
		free(&arena->all_players[i]);
		i++;
	}
	free(arena->all_players);
}

int main(int argc, char **argv)
{
	t_arena			arena;

	if (argc < 2)
	{
		print("usage: vm [player_count][.cor]\n");
		return (0);
	}
	vm_init_arena(&arena, argc, argv);
	vm_free_arena(&arena);
	return (0);
}
