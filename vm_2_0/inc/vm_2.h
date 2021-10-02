#ifndef VM_H
# define VM_H

# include "../../inc/corewar.h"

# define CYCLE_TO_DIE			1536
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

t_uint8	g_endianness = LITTLE;

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
	t_arg		opcode;
	t_arg		acb;
	t_arg		args[3];
}	t_instr;

typedef struct s_player
{
	t_header	header;
	t_byte		program[CHAMP_MAX_SIZE];
}	t_player;

typedef struct s_acb
{
	t_uint8		arg[3];
}	t_acb;

typedef struct s_buff
{
	t_byte		*mem;
	t_size		pos;
	t_size		len;
}	t_buff;


typedef struct s_process
{
	t_uint32	id;
	t_size		pc;
	t_bool		zf;
	t_int32		last_live;
	t_int32		cycles_before_execution;
	t_instr		*current_instruction;
	t_reg		registers[REG_NUMBER];
}	t_process;

typedef struct s_arena
{
	t_player	players[MAX_PLAYERS];
	t_size		player_count;
	t_buff		buffer;
	t_size		offset;
	t_process	*processes;
	t_size		current_cycle;
	t_size		cycle_to_die;
}	t_arena;

#endif
