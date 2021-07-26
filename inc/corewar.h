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

#include "../lib/core/inc/core.h"

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

#define	EMPTY					0U
#define T_REG					1U
#define T_DIR					1U << 1U
#define T_IND					1U << 2U
#define T_LAB					1U << 3U

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct s_player
{
	t_header	header;
	// 32 bit identfier.
	t_uint32	id;

	// Program counter. Initialized at player id.
	t_byte		*pc;

	// Zero flag, Along with a carry flag, a sign flag and an overflow flag,
	// the zero flag is used to check the result of an arithmetic operation,
	// including bitwise logical instructions. Initalized at 0.
	t_bool		zf;

	// 32 bit registers 1 - 16
	t_uint32	r1; // Initialized at player ID.
	t_uint32	r2; // Rest initialized at 0.
	t_uint32	r3;
	t_uint32	r4;
	t_uint32	r5;
	t_uint32	r6;
	t_uint32	r7;
	t_uint32	r8;
	t_uint32	r9;
	t_uint32	r10;
	t_uint32	r11;
	t_uint32	r12;
	t_uint32	r13;
	t_uint32	r14;
	t_uint32	r15;
	t_uint32	r16;
}	t_player;

typedef struct s_instructions
{
	t_byte	*bytes;
	t_size	size;
}	t_instructions;

typedef struct s_header
{
  t_uint32		magic;
  t_uint32		prog_size;
  char			prog_name[PROG_NAME_LENGTH + 1];
  char			comment[COMMENT_LENGTH + 1];
}	t_header;

typedef struct s_arena
{
	t_player	*all_players;
	t_size		player_count;
	t_byte		mem[MEM_SIZE];
	t_size		offset;
}	t_arena;

typedef struct s_arg_flags
{
	t_uint8		param1;
	t_uint8		param2;
	t_uint8		param3;
}	t_arg_flags;

typedef struct s_op
{
	const char	*code;
	t_uint32	arg_count;
	t_arg_flags	arg_flags;
	t_uint8		number;
	t_uint32	cycles;
	const char	*description;
	int			unknown1;
	int			unknown2;
}	t_op;

const t_op    g_op_tab[17] =
{
	{"live", 1, {T_DIR, EMPTY, EMPTY}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, EMPTY}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, EMPTY}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "substraction", 1, 0},
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