#ifndef VM_H
# define VM_H

# include "../../inc/corewar.h"
# include "../src/instr/instr.h"

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define VM_VERBOSE_LIVES		1
# define VM_VERBOSE_CYCLES		2
# define VM_VERBOSE_OPS			4
# define VM_VERBOSE_DEATHS		8
# define VM_VERBOSE_PC			16

# define VM_PRINT_ARENA_WIDTH	64

# define LITTLE 0
# define BIG 1

// Colours for printing.

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

# define ROW_SIZE 64

static const t_uint8	g_endianness = LITTLE;

typedef struct s_input_args
{
	char		*player_paths[MAX_PLAYERS];
	int			player_numbers[MAX_PLAYERS];
	int			next_player_nbr;
	int			player_count;
	int			verbosity;
	int			pause_nbr_cycles;
	int			coloured_output;
	int			dump_nbr_cycles;
}	t_input_args;

typedef struct s_reg
{
	t_byte		mem[REG_SIZE];
	t_size		len;
}	t_reg;

typedef struct s_arg
{
	t_reg		data;
	t_uint8		type;
	t_uint8		promoted;
}	t_arg;

typedef struct s_instr
{
	t_op		*op;
	t_byte		opcode;
	t_byte		acb;
	t_arg		args[3];
}	t_instr;

typedef struct s_player
{
	t_header	header;
//	t_byte		program[CHAMP_MAX_SIZE];
}	t_player;

typedef struct s_acb
{
	t_uint8		arg[3];
}	t_acb;

typedef struct s_mem
{
	t_byte		*mem;
	t_size		pos;
	t_size		len;
}	t_mem;


typedef struct s_process
{
	t_uint32	id;
	t_size		pc;
	t_bool		zf;
	t_size		last_live;
	t_int32		cycles_before_execution;
	t_instr		current_instruction;
	t_reg		registers[REG_NUMBER];
	struct s_process	*next;
}	t_process;

typedef struct s_arena
{
	t_mem		mem;
	t_header	players[MAX_PLAYERS];
	t_size		player_count;
	t_mem		buffer;
	t_size		offset;
	t_process	*processes;
	t_size		current_cycle;
	t_size		cycle_to_die;
	t_size		cycles_since_check;
	t_size		lives_since_check;
	t_size		checks_performed;
	t_size		last_player_alive;
	t_size		dump_nbr_cycles;
	t_size		pause_nbr_cycles;
	t_int32		verbosity;
	t_bool		coloured_output;
}	t_arena;

typedef void (*t_exec)(t_arena *, t_process *);

void	vm_save_input(
		t_arena *arena,
		t_uint32 argc,
		char **argv);

t_input_args	vm_parse_arguments(
		int argc,
		char **argv);
void	vm_mem_free(t_mem *src);
void	vm_mem_increment_pos(t_mem *src, t_size i);
t_mem	*vm_mem_new(t_mem *src, t_size len);
void	vm_mem_print_overlay(t_mem *src, t_size start, t_size len, char *colour);
void	vm_mem_print(t_mem *src);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);
t_mem	*vm_mem_set_pos(t_mem *src, t_size pos);
t_bool	vm_mem_write(t_mem *dst, t_byte *src, size_t src_len);
void	vm_reg_copy(t_reg *dst, t_reg *src);
void	vm_reg_deref(t_byte *dst, t_reg *src);
void	vm_reg_print(t_reg *src, char *colour);
void	vm_reg_ref(t_reg *dst, t_byte *src);
t_reg	*vm_reg_set(t_reg *src, t_size len);
void	vm_battle(t_arena arena);
void	vm_create_player(t_arena *arena, t_int32 *player_number, char *name);
t_process	*vm_create_process(t_arena arena, t_process *process_lst, \
t_int32 player_id);
void	vm_introduce_champs(t_arena arena);
void	vm_execute_cycle(t_process *process, t_arena *arena);
void	vm_pause_and_print_memory(
		t_arena arena);
		void	vm_check_live(t_process **head, t_arena *arena);
void	vm_exit_error(const char *message);
void	*vm_reverse_bytes(void *dst, void *src, t_size size);
t_arg	*vm_arg_read(t_arg *dst, t_mem *src);
t_arg	*vm_arg_new(t_arg *dst, t_uint8 type, t_uint8 promoted);
void	vm_print_arena(t_arena arena, t_process *process_list);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);
void	vm_mem_increment_pos(t_mem *src, t_size i);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);

#endif
