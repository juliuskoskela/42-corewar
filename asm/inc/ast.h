#ifndef AST_H
# define AST_H

# include "asm.h"

typedef enum e_astnode_type
{
	NONE = 0,
	REGISTER = 1,
	DIRECT = 2,
	INDIRECT = 4,
	LABEL = 8,
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

static const char	*g_astnode_types[15] =
{
	"PROGRAM",
	"STATEMENT_LIST",
	"STATEMENT",
	"LABEL",
	"DIRECTIVE",
	"CMD",
	"CMD_STRING",
	"INSTRUCTION",
	"COMMENT",
	"PARAMETER_LIST",
	"REGISTER",
	"INTEGER",
	"DIRECT",
	"INDIRECT",
	"NONE",
};

typedef struct s_astnode
{
	t_astnode_type		type;
	char				*value;
	t_token				token;
	struct s_astnode	*left_child;
	struct s_astnode	*right_child;
}	t_astnode;

t_astnode	*astnode_new(t_astnode_type type, char *value, t_token token);

#endif
