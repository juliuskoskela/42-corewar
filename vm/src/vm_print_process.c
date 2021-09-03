#include "vm.h"

void	vm_print_registers(t_process *p)
{
	t_size i;

	i = 0;
	while (i < 16)
	{
		print("R%d = ", i + 1);
		vm_print_bytes(p->registers[i], REG_SIZE);
		print("\n");
		i++;
	}
}

void	vm_print_process(t_process *p)
{
	print("%s\n", p->header.prog_name);
	print(
"{\n\
	magic = %u;\n\
	size = %u;\n\
	comment = %s;\n\
	current_instr = %s;\n\
	id = %u;\n\
	last_live = %d;\n\
	cycles_before_execution = %llu;\n\
	pc = %llu;\n\
	zf = %u;\n\
	next = %p;\n\
}\n", p->header.magic,
	p->header.prog_size,
	p->header.comment,
	p->current_instruction.mnemonic,
	p->id,
	p->last_live,
	p->cycles_before_execution,
	p->pc,
	p->zf,
	p->next);
	vm_print_registers(p);
}
