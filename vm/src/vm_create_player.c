#include "vm.h"

static void	vm_read_header(t_arena *arena, t_uint32 player_number, int fd)
{
	t_header	*player;
	t_byte		buf[COMMENT_LENGTH + 1];

	mzero(buf, COMMENT_LENGTH + 1);
	player = &arena->all_players[player_number - 1];
	if (read(fd, buf, sizeof(t_byte) * 4) != 4)
		vm_error("Invalid bytes in input file\n");
	player->magic = *(t_uint32 *)vm_reverse_bytes(\
		&player->magic, (void *)buf, sizeof(t_uint32));
	if (read(fd, buf, sizeof(t_byte) * PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		vm_error("Invalid bytes in input file\n");
	s_cpy(player->prog_name, (const char *)buf);
	if (read(fd, buf, sizeof(t_byte) * 4) != 4)
		vm_error("Invalid bytes in inputfile\n");
	player->prog_size = *(t_uint32 *)vm_reverse_bytes(\
		(void *)&player->prog_size, (void *)buf, sizeof(t_uint32));
	if (player->prog_size > CHAMP_MAX_SIZE)
		vm_error("Program size is larger than CHAMP_MAX_SIZE\n");
	if (read(fd, buf, COMMENT_LENGTH) != COMMENT_LENGTH)
		vm_error("Invalid bytes in inputfilen\n");
	s_cpy(player->comment, (const char *)buf);
}

/*
** Reading the last prog_size bytes of the input file and saving them to
** arena->mem. Checking that the size of the file == prog_size.
** offset (MEM_SIZE / player_count) bytes of memory will be available for each
** player.
*/

static void	vm_read_program(t_arena *arena, t_uint32 player_number, int fd)
{
	t_uint32	player_mem_location;
	t_size		check;

	player_mem_location = (player_number - 1) * arena->offset;
	check = read(fd, arena->mem + player_mem_location, \
		arena->all_players[player_number - 1].prog_size);
	if (check != arena->all_players[player_number - 1].prog_size)
		vm_error("Invalid amount of bytes in program\n");
}

void	vm_create_player(t_arena *arena, t_uint32 *player_number, char *name)
{
	t_header	player;
	int			fd;

	if (arena->all_players[*player_number - 1].prog_size || \
		arena->all_players[*player_number - 1].prog_name[0])
		*player_number += 1;
	if (*player_number > MAX_PLAYERS)
		vm_error("player_number is not within MAX_PLAYERS\n");
	mzero(&player, sizeof(t_header));
	arena->all_players[*player_number - 1] = player;
	if (s_cmp(".cor", s_rchr(name, '.')))
		vm_error("Champions must be .cor files\n");
	fd = open(name, O_RDONLY);
	if (fd < 0)
		vm_error("Unable to open .cor file \n");
	vm_read_header(arena, *player_number, fd);
	if (arena->all_players[*player_number - 1].magic != COREWAR_EXEC_MAGIC)
		vm_error("COREWAR_EXEC_MAGIC does not match the bytecode\n");
	vm_read_program(arena, *player_number, fd);
	*player_number += 1;
	close(fd);
}
