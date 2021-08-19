#include "asm.h"

void	asm_init_output_data(t_output_data *data)
{
	mset(data, 0, sizeof(*data));
	data->header.magic = COREWAR_EXEC_MAGIC;
}
