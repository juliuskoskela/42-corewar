#include "vm.h"

void	vm_test_print_processes(t_process *lst)
{
	while (lst)
	{
		print("Process id:\t%d\n", lst->id);
		print("pc:\t\t%p\n", lst->pc);
		print("zf:\t\t%d\n", lst->zf);
		print("Registers\t1: |%x|\t2: |%x|\t3 :|%x|\t4: |%x|\n\
		5: |%d|\t6: |%d|\t7: |%d|\t8: |%d|\n\
		9: |%d|\t10: |%d|\t11: |%d|\t12: |%d|\n\
		13: |%d|\t14: |%d|\t15: |%d|\t16: |%d|\n",
		lst->registers[1], lst->registers[2], lst->registers[3], lst->registers[4],
		lst->registers[5], lst->registers[6], lst->registers[7], lst->registers[8], 
		lst->registers[9], lst->registers[10], lst->registers[11], lst->registers[12],
		lst->registers[13], lst->registers[14], lst->registers[15], lst->registers[16]);
		lst = lst->next;
	}
}

void	vm_test_print_program(t_arena arena)
{
	t_uint32	player;
	t_uint32	byte_i;
	t_byte		byte;

	player = 1;
	byte_i = 0;
	while (player * arena.offset <= MEM_SIZE)
	{
		print("player %d memory:\n", player);
		while (byte_i < player * arena.offset)
		{
			byte = arena.mem[byte_i++];
			print("%x ", byte);
		}
		print("\n");
		player++;
	}
}

void	vm_test_print_header(t_header player)
{
	print("magic: %x\n", player.magic);
	print("prog_size: %d\n", player.prog_size);
	print("prog_name : %s\n", player.prog_name);
	print("comment: %s\n", player.comment);
}

void	vm_test_print_arena(t_arena arena)
{
	t_uint32	i;

	i = 0;
	print("player_count: %d\n", arena.player_count);
	print("arena offset: %d\n", arena.offset);
	while (i < arena.player_count)
	{
		print("player %d header:\n", i + 1);
		vm_test_print_header(arena.all_players[i]);
		i++;
	}
	vm_test_print_program(arena);
}
