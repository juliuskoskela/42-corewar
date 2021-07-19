///////////////////////////////////////////////////////////////////////////////
///
/// asm.h
///
/// \authors Satu Koskinen, Kalle Suomala, Julius Koskela
///
/// \brief
///
///////////////////////////////////////////////////////////////////////////////

#ifndef ASM_H
# define ASM_H

//# include "corewar.h"

# include <string.h>
# include <stdint.h>

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define EMPTY				0
# define T_REG				1U
# define T_DIR				1U << 1U
# define T_IND				1U << 2U
# define T_LAB				1U << 3U

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

typedef struct s_astnode t_astnode;

typedef enum e_token_type
{
	NO_TOKEN,
	ID_TOKEN,
	INTEGER_TOKEN,
	NEWLINE_TOKEN,
	DOT_TOKEN,
	STRING_TOKEN,
	COMMENT_TOKEN,
	LABEL_TOKEN,
	DIRECT_TOKEN,
	SEPARATOR_TOKEN,
	EOF_TOKEN,
	ERROR_TOKEN
}	t_token_type;

static const char	*g_token_types[11] =
{
	"ID_TOKEN",
	"INTEGER_TOKEN",
	"NEWLINE_TOKEN",
	"DOT_TOKEN",
	"STRING_TOKEN",
	"COMMENT_TOKEN",
	"LABEL_TOKEN",
	"DIRECT_TOKEN",
	"SEPARATOR_TOKEN",
	"EOF_TOKEN",
	"ERROR_TOKEN"
};

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	size_t			file_row;
	size_t			file_col;
}	t_token;

typedef struct s_lexer
{
	const char		*input;
	size_t			current_pos;
	char			current_char;
	size_t			file_row;
	size_t			file_col;
}	t_lexer;

typedef struct s_parser
{
	t_lexer			*lexer;
	t_token			current_token;
	int				error_occurred;
}	t_parser;

typedef struct s_symbol_list
{
	char					*symbol;
	t_astnode				*node;
	struct s_symbol_list	*next;

}	t_symbol_list;

typedef struct s_arg_flags
{
	uint8_t		param1;
	uint8_t		param2;
	uint8_t		param3;
}	t_arg_flags;

typedef struct s_op
{
	const char	*mnemonic;
	uint32_t	arg_count;
	t_arg_flags	arg_flags;
	uint8_t		opcode;
	uint32_t	cycles;
	const char	*description;
	int			has_argument_coding_byte;
	int			unknown2;
}	t_op;

# define OP_COUNT			17

static const t_op    g_op_tab[17] =
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

typedef struct s_header
{
  uint32_t		magic;
  char			prog_name[PROG_NAME_LENGTH + 1];
  uint32_t		prog_size;
  char			comment[COMMENT_LENGTH + 1];
}	t_header;

char				*asm_read_input(const char *filepath);

t_lexer				asm_init_lexer(const char *input);
void				asm_lexer_advance(t_lexer *lexer);
char				asm_lexer_peek(t_lexer *lexer);
t_token				asm_init_token(t_token_type type, char *value, size_t row, size_t col);
t_token				asm_get_next_token(t_lexer *lexer);
t_token_type		asm_peek_next_token(t_lexer *lexer);

t_parser			asm_init_parser(t_lexer *lexer);
int					asm_parse(t_astnode **tree, t_parser *parser);
int					asm_validate_ast(t_astnode *tree);

void				asm_print_ast_dot(int fd, t_astnode *tree);

void				asm_exit_error(char *msg);

#endif
