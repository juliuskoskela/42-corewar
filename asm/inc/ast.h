#ifndef AST_H
# define AST_H

# include "asm.h"

typedef enum e_astnode_type
{
	NONE = 0,
	REGISTER = 1,
	DIRECT = 2,
	INDIRECT = 4,
	LABEL,
	PROGRAM,
	STATEMENT_LIST,
	STATEMENT,
	DIRECTIVE,
	CMD,
	CMD_STRING,
	INSTRUCTION,
	COMMENT,
	PARAMETER_LIST,
	INTEGER,
}	t_astnode_type;

static const char *const	g_astnode_types[17] =
{
	"NONE",
	"REGISTER",
	"DIRECT",
	NULL,
	"INDIRECT",
	"LABEL",
	"PROGRAM",
	"STATEMENT_LIST",
	"STATEMENT",
	"DIRECTIVE",
	"CMD",
	"CMD_STRING",
	"INSTRUCTION",
	"COMMENT",
	"PARAMETER_LIST",
	"INTEGER",
};

typedef struct s_astnode
{
	t_astnode_type		type;
	char				*value;
	int32_t				num_value;
	t_token				token;
	struct s_astnode	*left_child;
	struct s_astnode	*right_child;
}	t_astnode;

t_astnode	*asm_astnode_new(t_astnode_type type, char *value, t_token token);
void		asm_astnode_free(t_astnode *tree);

#endif
