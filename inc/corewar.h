#ifndef COREWAR_H
# define COREWAR_H

///////////////////////////////////////////////////////////////////////////////
///
/// corewar.h
///
/// \authors Satu Koskinen, Kalle Suomala, Julius Koskela
///
/// \brief Common header for Corewar.
///
///////////////////////////////////////////////////////////////////////////////

# include "../lib/core/inc/core.h"

# define REG_ADDR_SIZE			1
# define IND_ADDR_SIZE			2
# define DIR_VAL_SIZE			2

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define EMPTY					0U
# define T_REG					1U
# define T_DIR					(1U << 1U)
# define T_IND					(1U << 2U)
# define T_LAB					(1U << 3U)

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_SIZE				4
# define REG_NUMBER				16

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_header
{
	t_uint32		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	t_uint32		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}	t_header;

typedef struct s_param_types
{
	t_uint8		param1;
	t_uint8		param2;
	t_uint8		param3;
}	t_param_types;

typedef struct s_op
{
	const char		*mnemonic;
	t_uint32		param_count;
	t_param_types	param_types;
	t_uint8			opcode;
	t_uint32		cycles;
	const char		*description;
	int				has_argument_coding_byte;
	int				unknown;
}	t_op;

# define OP_COUNT	16

static const t_op	g_op_tab[] =
{
	{"live", 1, {T_DIR, EMPTY, EMPTY}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, EMPTY}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, EMPTY}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "subtraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, EMPTY, EMPTY}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR, EMPTY, EMPTY}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, EMPTY}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR, EMPTY, EMPTY}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, EMPTY, EMPTY}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};


#endif
