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

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef struct s_process
{
	struct s_header		header;
	struct s_process	*next;
	t_instructions		next_instruction;
	t_uint32			id;
	t_int32				last_live;
	t_int32				cycles_before_execution;
	// Program counter.
	// t_byte				*pc;
	t_size				pc;

	// Zero flag, Along with a carry flag, a sign flag and an overflow flag,
	// the zero flag is used to check the result of an arithmetic operation,
	// including bitwise logical instructions. Initialized at 0.
	t_bool				zf;

	// 32 bit registers 1 - 16, r1 initialized at player ID and the rest at 0
	t_uint64			registers[17];
}	t_process;

typedef struct s_arena
{
	t_header	all_players[MAX_PLAYERS];
	t_size		player_count;
	t_byte		mem[MEM_SIZE];
	t_size		offset;
	// if -dump flag is missing, this will be 0.
	t_int32		dump_nbr_cycles;
}	t_arena;

typedef struct s_battle
{
	//the player who was last reported to be alive
	t_int32	last_alive;
	//number of cycles executed since starting the program.
	t_int32	cycles_executed;
	// number of lives reported within current cycle_to_die period.
	t_int32	lives_since_check;
	// number of checks with lives_since_check < NBR_LIVE. if this reaches
	// MAX_CHECKS, cycle_to_die is decreased by CYCLE_DELTA and
	// checks_performed is set to 0.
	t_int32	checks_performed;
	// every cycle_to_die cycles, each process will be checked for a live.
	t_int32	cycle_to_die;
	t_int32	cycles_since_check;
}	t_battle;

typedef void (*t_instr)(t_arena *, t_process *);

void		vm_error(const char *message);
void		vm_save_input(t_arena *arena, t_uint32 argc, char **argv);
void		vm_create_player(t_arena *arena, t_uint32 *player_number, \
char *name);
void		*vm_reverse_bytes(void *dst, void *src, t_size size);
void		vm_check_live(t_process **processes, t_battle *battle);
void		vm_execute_cycle(t_process *processes, t_battle *battle, t_arena *arena);
void		vm_introduce_champs(t_arena arena);

void		vm_test_print_arena(t_arena arena);
void		vm_test_print_processes(t_process *lst);
void		vm_battle(t_arena arena);
void		vm_print_arena(t_arena arena, t_process *process_list);

void vm_instr_st(
		t_arena *a,
		t_process *p);

void vm_instr_sti(
		t_arena *a,
		t_process *p);

void vm_instr_null(
		t_arena *a,
		t_process *p);

t_uint8	vm_check_acb(
		t_uint8 acb,
		t_size arg_i);

static const t_instr g_inst[] =
{
	vm_instr_null,
	vm_instr_null,
	vm_instr_st,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_sti,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
	vm_instr_null,
};

#endif
