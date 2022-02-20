#include "vm.h"

/*
static void	vm_read_header_subject(t_arena *arena, t_uint32 player_number, int fd)
{
	t_header	*player;
	t_byte		buf[COMMENT_LENGTH + 1];

	mzero(buf, COMMENT_LENGTH + 1);
	player = &arena->players[player_number - 1];
	if (read(fd, buf, sizeof(player->magic)) != sizeof(player->magic))
		vm_exit_error("Invalid bytes in input file\n");
	player->magic = *(t_uint32 *)vm_reverse_bytes(\
		&player->magic, (void *)buf, sizeof(player->magic));
	if (read(fd, buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		vm_exit_error("Invalid bytes in input file\n");
	s_cpy(player->prog_name, (const char *)buf);
	//read sizeof(player->prog_size) == 32 bits. This differs in subject and our corewar.
	if (read(fd, buf, sizeof(player->prog_size_subject)) != sizeof(player->prog_size_subject))
		vm_exit_error("Invalid bytes in input file\n");
	player->prog_size_subject = *(t_uint32 *)vm_reverse_bytes(\
		(void *)&player->prog_size_subject, (void *)buf, sizeof(player->prog_size_subject));
	player->prog_size = player->prog_size_subject;
	if (player->prog_size > CHAMP_MAX_SIZE)
		vm_exit_error("Program size is larger than CHAMP_MAX_SIZE\n");
	if (read(fd, buf, COMMENT_LENGTH) != COMMENT_LENGTH)
		vm_exit_error("Invalid bytes in input file\n");
	s_cpy(player->comment, (const char *)buf);
}
*/

static void	vm_read_header(t_arena *arena, int player_number, int fd)
{
	t_header	*player;
	t_byte		buf[COMMENT_LENGTH + 1];

	mzero(buf, COMMENT_LENGTH + 1);
	player = &arena->players[player_number - 1];
	if (read(fd, buf, sizeof(player->magic)) != sizeof(player->magic))
		vm_exit_error("Invalid bytes in input file\n");
	player->magic = *(t_uint32 *)vm_reverse_bytes(&player->magic,
		(void *)buf, sizeof(player->magic));
	if (read(fd, buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		vm_exit_error("Invalid bytes in input file\n");
	s_cpy(player->prog_name, (const char *)buf);
	if (read(fd, buf, sizeof(player->prog_size)) != sizeof(player->prog_size))
		vm_exit_error("Invalid bytes in input file\n");
	player->prog_size = *(t_uint32 *)vm_reverse_bytes(\
		(void *)&player->prog_size, (void *)buf, sizeof(player->prog_size));
	if (player->prog_size > CHAMP_MAX_SIZE)
		vm_exit_error("Program size is larger than CHAMP_MAX_SIZE\n");
	if (read(fd, buf, COMMENT_LENGTH) != COMMENT_LENGTH)
		vm_exit_error("Invalid bytes in input file\n");
	s_cpy(player->comment, (const char *)buf);
}

/*
** Reading the last prog_size bytes of the input file and saving them to
** arena->mem. Checking that the size of the file == prog_size.
** offset (MEM_SIZE / player_count) bytes of memory will be available for each
** player.
*/

static void	vm_read_program(t_arena *arena, int player_number, int fd)
{
	t_byte		program[CHAMP_MAX_SIZE];
	t_size		program_size;
	t_size		player_mem_location;

	player_mem_location = ((t_size)player_number - 1) * arena->offset;
	program_size = arena->players[player_number - 1].prog_size;
	if (read(fd, program, program_size) != (ssize_t)program_size)
		vm_exit_error("Invalid amount of bytes in program\n");
	vm_mem_set_pos(&arena->mem, player_mem_location);
	vm_mem_write(&arena->mem, program, program_size);
}

void	vm_create_player(t_arena *arena, int *player_number, char *name)
{
	t_header	player;
	int			fd;

	if (*player_number > MAX_PLAYERS)
		vm_exit_error("Player number is not within MAX_PLAYERS\n");
	if (arena->players[*player_number - 1].prog_size || \
		arena->players[*player_number - 1].prog_name[0])
		*player_number += 1;
	mzero(&player, sizeof(t_header));
	arena->players[*player_number - 1] = player;
	if (s_cmp(".cor", s_rchr(name, '.')))
		vm_exit_error("Champions must be .cor files\n");
	fd = open(name, O_RDONLY);
	if (fd < 0)
		vm_exit_error("Unable to open .cor file\n");
	vm_read_header(arena, *player_number, fd);
	if (arena->players[*player_number - 1].magic != COREWAR_EXEC_MAGIC)
		vm_exit_error("COREWAR_EXEC_MAGIC does not match the bytecode\n");
	vm_read_program(arena, *player_number, fd);
	*player_number += 1;
	close(fd);
}
