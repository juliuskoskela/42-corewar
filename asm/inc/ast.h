#ifndef AST_H
# define AST_H

typedef enum e_astnode_type
{
	PROGRAM,
	STATEMENT_LIST,
	STATEMENT,
	LABEL,
	DIRECTIVE,
	CMD,
	CMD_STRING,
	INSTRUCTION,
	COMMENT,
	PARAMETER_LIST,
	REGISTER,
	INTEGER,
	DIRECT,
	INDIRECT,
	NONE,
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
	struct s_astnode	*left_child;
	struct s_astnode	*right_child;
}	t_astnode;

#endif
