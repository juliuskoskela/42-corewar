#include "vm.h"

t_size	vm_instr_size(t_instr *src)
{
	return (
		sizeof(src->opcode)
		+ src->op->has_argument_coding_byte
		+ src->args[0].data.len
		+ src->args[1].data.len
		+ src->args[2].data.len);
}
