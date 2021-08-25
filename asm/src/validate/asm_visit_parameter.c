#include "asm.h"
#include "ast.h"
#include "validate.h"

static void	asm_visit_register(t_astnode *node)
{
	char	*value;
	int		reg_number;

	value = node->value;
	if (*value != 'r')
		asm_semantic_error(node, "Invalid register");
	reg_number = s_toi(&value[1]);
	if (reg_number < 1 || reg_number > REG_NUMBER)
		asm_semantic_error(node, "Invalid register");
}

void	asm_visit_parameter(t_astnode *node, uint32_t param_nbr,
t_op instruction)
{
	uint8_t	type;
	uint8_t	allowed_param_types;

	type = (uint8_t)node->type;
	if (param_nbr == 1)
		allowed_param_types = instruction.param_types.param1;
	else if (param_nbr == 2)
		allowed_param_types = instruction.param_types.param2;
	else
		allowed_param_types = instruction.param_types.param3;
	if ((type & allowed_param_types) == 0)
		asm_semantic_error(node, "Invalid argument type");
	if (node->type == REGISTER)
		asm_visit_register(node);
}
