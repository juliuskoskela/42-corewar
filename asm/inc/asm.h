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

# include "ast.h"

# include <string.h>

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

typedef enum e_token_type
{
	ID_TOKEN,
	INTEGER_TOKEN,
	NEWLINE_TOKEN,
	DOT_CMD_TOKEN,
	STRING_TOKEN,
	COMMENT_TOKEN,
	LABEL_TOKEN,
	DIRECT_TOKEN,
	SEPARATOR_TOKEN,
	EOF_TOKEN,
	ERROR_TOKEN
}					t_token_type;

static const char	*g_token_types[11] =
{
	"ID_TOKEN",
	"INTEGER_TOKEN",
	"NEWLINE_TOKEN",
	"DOT_CMD_TOKEN",
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
}					t_token;

typedef struct s_lexer
{
	const char		*input;
	size_t			current_pos;
	char			current_char;
	size_t			file_row;
	size_t			file_col;
}					t_lexer;

typedef struct s_parser
{
	t_lexer			*lexer;
	t_token			current_token;
}					t_parser;

char				*asm_read_input(const char *filepath);

t_lexer				asm_init_lexer(const char *input);
void				asm_lexer_advance(t_lexer *lexer);
t_token				asm_get_next_token(t_lexer *lexer);
t_token_type		asm_peek_next_token(t_lexer *lexer);

t_parser			asm_init_parser(t_lexer *lexer);
t_astnode			*asm_parse(t_parser *parser);

void				asm_print_ast_dot(t_astnode *tree);

void				asm_exit_error(char *msg);

#endif
