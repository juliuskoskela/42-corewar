#include "vm.h"

void	vm_test_print_header(t_player player)
{
	print("magic: %x\n", player.header.magic);
	print("prog_size: %d\n", player.header.prog_size);
	print("prog_name : %s\n", player.header.prog_name);
	print("comment: %s\n", player.header.comment);
}

void    vm_test_print_arena(t_arena arena)
{
	t_uint32 i;

	i = 0;
	print("player_count: %d\n", arena.player_count);
	print("arena offset: %d\n", arena.offset);
	while (i < arena.player_count)
	{
		print("player %d header:\n", arena.all_players[i].number);
		vm_test_print_header(arena.all_players[i]);
		i++;
	}
}