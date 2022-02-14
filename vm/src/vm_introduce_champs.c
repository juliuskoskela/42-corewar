#include "vm.h"

void	vm_introduce_champs(t_arena arena)
{
	t_size	i;

	print("Introducing contestants...\n");
	i = 0;
	while (i < arena.player_count)
	{
		print("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", \
		i + 1, arena.players[i].prog_size, \
		arena.players[i].prog_name, arena.players[i].comment);
		i++;
	}
}
