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

# define VM_VERBOSE_LIVES		1
# define VM_VERBOSE_CYCLES		2
# define VM_VERBOSE_OPS			4
# define VM_VERBOSE_DEATHS		8
# define VM_VERBOSE_PC			16

# define VM_PRINT_ARENA_WIDTH	32

typedef t_byte* t_mem_addr;
typedef t_uint64* t_reg_addr;

typedef struct s_instruction
{
	t_op	instruction;
	t_byte	acb;
}	t_instruction;

typedef struct s_process
{
	struct s_header		header;
	t_instruction		next_instruction;
	t_uint32			id;
	t_int32				last_live;
	t_int32				cycles_before_execution;
	// Program counter.
	// t_byte			*pc;
	t_size				pc;

	// Zero flag, Along with a carry flag, a sign flag and an overflow flag,
	// the zero flag is used to check the result of an arithmetic operation,
	// including bitwise logical instructions. Initialized at 0.
	t_bool				zf;

	// 32 bit registers 1 - 16, r1 initialized at player ID and the rest at 0
	t_uint64			registers[16];
	struct s_process	*next;
}	t_process;

typedef struct s_arena
{
	t_header	all_players[MAX_PLAYERS];
	t_size		player_count;
	t_byte		mem[MEM_SIZE];
	t_size		offset;

	t_process	*processes;
	// if -dump flag is missing, this will be 0.
	t_int32		dump_nbr_cycles;
	// if -v flag is missing, this will be 0
	t_int32		verbosity;
	// the player who was last reported to be alive
	t_int32		last_player_alive;
	// number of cycles executed since starting the program.
	t_int32		cycles_executed;
	// number of lives reported within current cycle_to_die period.
	t_int32		lives_since_check;
	// number of checks with lives_since_check < NBR_LIVE. if this reaches
	// MAX_CHECKS, cycle_to_die is decreased by CYCLE_DELTA and
	// checks_performed is set to 0.
	t_int32		checks_performed;
	// every cycle_to_die cycles, each process will be checked for a live.
	t_int32		cycle_to_die;
	t_int32		cycles_since_check;
}	t_arena;

typedef void (*t_instr)(t_arena *, t_process *);

void vm_error(
		const char *message);

void vm_save_input(
		t_arena *arena,
		t_uint32 argc,
		char **argv);

void vm_create_player(
		t_arena *arena,
		t_int32 *player_number,
		char *name);

t_process	*vm_create_process(
		t_arena arena,
		t_process *process_lst,
		t_uint64 player_id);

void *vm_reverse_bytes(
		void *dst,
		void *src,
		t_size size);

void vm_check_live(
		t_process **processes,
		t_arena *arena);

void vm_execute_cycle(
		t_process *processes,
		t_arena *arena);

void vm_introduce_champs(
		t_arena arena);

void vm_test_print_arena(
		t_arena arena);

void vm_test_print_processes(
		t_process *lst);

void vm_battle(
		t_arena arena);

void vm_print_arena(
		t_arena arena,
		t_process *process_list);

void vm_instr_live(
		t_arena *a,
		t_process *p);

void vm_instr_add(
		t_arena *a,
		t_process *p);

void vm_instr_sub(
		t_arena *a,
		t_process *p);

void vm_instr_and(
		t_arena *a,
		t_process *p);

void vm_instr_or(
		t_arena *a,
		t_process *p);

void vm_instr_xor(
		t_arena *a,
		t_process *p);

void vm_instr_ld(
		t_arena *a,
		t_process *p);

void vm_instr_st(
		t_arena *a,
		t_process *p);

void vm_instr_zjmp(
		t_arena *a,
		t_process *p);

void vm_instr_ldi(
		t_arena *a,
		t_process *p);

void vm_instr_sti(
		t_arena *a,
		t_process *p);

void vm_instr_fork(
		t_arena *a,
		t_process *p);

void vm_instr_lld(
		t_arena *a,
		t_process *p);

void vm_instr_lldi(
		t_arena *a,
		t_process *p);

void vm_instr_lfork(
		t_arena *a,
		t_process *p);

void vm_instr_aff(
		t_arena *a,
		t_process *p);

void vm_instr_null(
		t_arena *a,
		t_process *p);

t_uint8	vm_check_acb(
		t_uint8 acb,
		t_size arg_i);

t_reg_addr vm_get_reg_addr(
		t_process *p,
		t_size i);

t_mem_addr vm_get_mem_addr(
		t_arena *a,
		t_size i);

t_int64 vm_get_val(
		t_arena *a,
		t_process *p,
		t_uint8 acb,
		t_size *mem_i);

void	vm_advance_pc(
		t_size *pc,
		int size);

static const t_instr g_instr_funcs[] =
{
	vm_instr_live,
	vm_instr_ld,
	vm_instr_st,
	vm_instr_add,
	vm_instr_sub,
	vm_instr_and,
	vm_instr_or,
	vm_instr_xor,
	vm_instr_zjmp,
	vm_instr_ldi,
	vm_instr_sti,
	vm_instr_fork,
	vm_instr_lld,
	vm_instr_lldi,
	vm_instr_lfork,
	vm_instr_aff
};

#endif
