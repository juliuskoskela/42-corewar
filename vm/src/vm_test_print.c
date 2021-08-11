#include "vm.h"

void	vm_test_print_processes(t_process *lst)
{
	while (lst)
	{
		print("Process id: %d\n", lst->id);
		print("pc: %p", lst->pc);
		print("zf: %d", lst->zf);
		print("Registers 1:|%x| 2:|%x| 3 :|%x| 4: |%x| 5: |%d| 6: |%d| 7: |%d|\
		 8: |%d| 9: |%d| 10 :|%d| 11:|%d| 12:|%d| 13: |%d| 14: |%d| 15: |%d| \
		 16:|%d|\n", lst->r1, lst->r2, lst->r3, \
		lst->r4, lst->r5, lst->r6, lst->r7, lst->r8, lst->r9, \
		lst->r10, lst->r11, lst->r12, lst->r13, lst->r14, \
		lst->r15, lst->r16);
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
