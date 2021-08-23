#include "asm.h"
#include "ast.h"
#include "validate.h"

int	asm_visit_parameter(t_astnode *node, uint32_t param_nbr, t_op instruction)
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
		return (asm_semantic_error(node, "Invalid argument"));
	return (1);
}
