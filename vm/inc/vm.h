#ifndef VM_H
# define VM_H

///////////////////////////////////////////////////////////////////////////////
///
/// vm.h
///
/// \authors Satu Koskinen, Kalle Suomala, Julius Koskela
///
/// \brief
///
///////////////////////////////////////////////////////////////////////////////

# include "../../inc/corewar.h"

typedef struct s_header
{
  t_uint32		magic;
  t_uint32		prog_size;
  char			prog_name[PROG_NAME_LENGTH + 1];
  char			comment[COMMENT_LENGTH + 1];
}	t_header;

typedef struct s_process
{

	struct s_header		header;
	// 32 bit identfier.
	struct s_process	*next;
	t_instructions		next_instruction;
	t_uint32			id;
	t_uint32			last_live;
	t_uint32			cycles_before_execution;
	// Program counter. Initialized at player id.
	t_byte				*pc;

	// Zero flag, Along with a carry flag, a sign flag and an overflow flag,
	// the zero flag is used to check the result of an arithmetic operation,
	// including bitwise logical instructions. Initalized at 0.
	t_bool				zf;

	// 32 bit registers 1 - 16
	t_uint32			r1; // Initialized at player ID.
	t_uint32			r2; // Rest initialized at 0.
	t_uint32			r3;
	t_uint32			r4;
	t_uint32			r5;
	t_uint32			r6;
	t_uint32			r7;
	t_uint32			r8;
	t_uint32			r9;
	t_uint32			r10;
	t_uint32			r11;
	t_uint32			r12;
	t_uint32			r13;
	t_uint32			r14;
	t_uint32			r15;
	t_uint32			r16;
}	t_process;

typedef struct s_arena
{
	t_header	all_players[MAX_PLAYERS];
	t_size		player_count;
	t_byte		mem[MEM_SIZE];
	t_size		offset;
	// if -dump flag is missing, this will be 0.
	t_size		dump_nbr_cycles;
}	t_arena;

typedef struct s_battle
{
	t_size	last_alive;
	t_size	cycles_executed;
	t_size	lives_since_check;
	t_size	checks_performed;
	t_size	cycle_to_die;
}	t_battle;

void	vm_error(const char *message);
void	vm_save_input(t_arena *arena, t_uint32 argc, char **argv);
void	vm_create_player(t_arena *arena, t_uint32 *player_number, char *name);
void	*vm_reverse_bytes(void *dst, void *src, t_size size);


void	vm_test_print_arena(t_arena arena);
void	vm_test_print_processes(t_process *lst);
void	vm_battle(t_arena arena);

#endif
