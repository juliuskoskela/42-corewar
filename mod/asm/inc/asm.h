#ifndef ASM_H
# define ASM_H
///////////////////////////////////////////////////////////////////////////////
///
/// asm.h
///
/// \authors Satu Koskinen, Kalle Suomala, Julius Koskela
///
/// \brief
///////////////////////////////////////////////////////////////////////////////

#include "../../../lib/core/inc/core.h"

typedef enum op_params
{
	T_DIR = 1,
	T_IND = 1 << 1,
	T_LAB = 1 << 2
}	t_op_params;

typedef enum e_tok_type
{
	I32,
	U32,
	F,
	S
}	t_tok_type;

typedef enum e_tok_func
{
	START_BLOCK,
	END_BLOCK,
	REG_EXA,
}	t_tok_func;

const char	*g_symbol [] =
{
	"{",
	"}",
	"exa",
};

typedef union u_tok_data
{
	int				i32;
	unsigned int	u32;
	float			f;
	char			*s;
}	t_tok_data;

typedef struct s_tok
{

}	t_tok;

#endif

