#include "instr.h"

t_size	vm_instr_size(t_instr *src)
{
	return (
		src->opcode.data.len
		+ src->acb.data.len
		+ src->args[0].data.len
		+ src->args[1].data.len
		+ src->args[2].data.len);
}
