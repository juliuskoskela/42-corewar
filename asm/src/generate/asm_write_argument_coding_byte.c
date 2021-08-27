#include "asm.h"
#include "ast.h"
#include "generate.h"

void	asm_write_argument_coding_byte(t_output_data *data, uint32_t *lc,
t_astnode *parameter_list)
{
	t_astnode	*parameter;
	uint8_t		acb;
	uint8_t		i;

	acb = 0;
	i = 6;
	if (data->verbose)
		print("arguments: ");
	while (parameter_list != NULL)
	{
		parameter = parameter_list->left_child;
		if (data->verbose)
			print("%s ", g_astnode_types[parameter->type]);
		if (parameter->type == REGISTER)
			acb = (uint8_t)(acb | (REG_CODE << i));
		else if (parameter->type == DIRECT)
			acb = (uint8_t)(acb | (DIR_CODE << i));
		else if (parameter->type == INDIRECT)
			acb = (uint8_t)(acb | (IND_CODE << i));
		i -= 2;
		parameter_list = parameter_list->right_child;
	}
	if (data->verbose)
		asm_print_output_info("\n=> write argument coding byte", NULL, acb);
	asm_write_bytes(data, lc, &acb, 1);
}
