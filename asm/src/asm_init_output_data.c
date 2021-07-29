#include "asm.h"

void	asm_init_output_data(t_output_data *data)
{
	memset(&data->header, 0, sizeof(t_header));
	memset(&data->symbols, 0, sizeof(t_symbol_list));
	memset(data->program, 0, sizeof(data->program));
	data->header.magic = COREWAR_EXEC_MAGIC;
}
