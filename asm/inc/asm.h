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

# include "corewar.h"

# include <string.h>
# include <stdint.h>

# define ASM_PRINT_DEBUG 1
# define BUF_SIZE 100

# define COMMENT_CHAR		'#'
# define COMMENT_SEMICOLON	';'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

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

static const char *const	g_token_types[] = {
	"NO_TOKEN",
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
	t_token_type			type;
	char					*value;
	size_t					line_no;
	size_t					col;
}	t_token;

typedef struct s_lexer
{
	const char				*input;
	size_t					current_pos;
	char					current_char;
	size_t					line_no;
	size_t					col;
}	t_lexer;

typedef struct s_parser
{
	t_lexer					*lexer;
	t_token					current_token;
	int						error_occurred;
}	t_parser;

typedef struct s_refnode
{
	uint32_t				ref_location;
	uint32_t				op_location;
	size_t					size;
	struct s_refnode		*next;
}	t_refnode;

typedef struct s_astnode	t_astnode;

typedef struct s_symbol_list
{
	char					*symbol;
	t_astnode				*node;
	t_refnode				*forward_refs;
	struct s_symbol_list	*next;

}	t_symbol_list;

typedef struct s_output_data
{
	t_symbol_list			symbols;
	t_header				header;
	int8_t					program[CHAMP_MAX_SIZE + 1];
}	t_output_data;

typedef struct s_input_args
{
	char	*input_path;
	int		print_ast_dot;
	int		print_hex_dump;
}	t_input_args;

char				*asm_read_input(const char *filepath);

void				asm_init_lexer(t_lexer *lexer, const char *input);
t_token				asm_init_token(t_token_type type, char *value,
						size_t row, size_t col);
t_token				asm_get_next_token(t_lexer *lexer);
t_token_type		asm_peek_next_token(t_lexer *lexer);
void				asm_init_parser(t_parser *parser, t_lexer *lexer);
void				asm_parse(t_astnode **tree, char *input);

void				asm_validate_ast(t_output_data *data, t_astnode *tree);

void				asm_init_output_data(t_output_data *data);
int					asm_generate_output(t_output_data *data,
						t_astnode *tree);
void				asm_write_output_to_file(char *path, t_output_data data);
void				asm_print_output_hexdump(t_output_data data);

t_symbol_list		*asm_symbol_list_new(t_astnode *node, char *symbol);
int					asm_symbol_list_define(t_symbol_list *list,
						t_astnode *node);
t_symbol_list		*asm_symbol_list_lookup(t_symbol_list *list, char *symbol);
int					asm_symbol_list_delete(t_symbol_list **list, char *symbol);
void				asm_symbol_list_free(t_symbol_list list);
void				asm_print_symbol_list(t_symbol_list *symbols,
						const char *title);

void				asm_write_ast_dot_to_file(char *path, t_astnode *tree);
void				asm_print_ast_dot(int fd, t_astnode *tree);

void				asm_exit_error(char *msg);
int					asm_get_instruction(t_op *dst, char *mnemonic);

#endif
