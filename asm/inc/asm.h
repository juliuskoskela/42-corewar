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
	ID, INTEGER, NEWLINE, DOT_CMD, STRING, COMMENT, LABEL, DIRECT, SEPARATOR, EOF_TOKEN, ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_lexer
{
	const char	*input;
	size_t		current_pos;
	char		current_char;
}				t_lexer;

char	*asm_read_input(const char *filepath);
t_lexer	asm_init_lexer(const char *input);
t_token	asm_get_next_token(t_lexer *lexer);
int		asm_parse(t_lexer *lexer);

void	asm_exit_error(char *msg);

#endif
