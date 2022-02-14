/// opcode:		8 (0x08)
/// mnemonic:	xor
/// name:		xor
/// params:		3 : { T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG }
/// acb:		true
/// ncycles:	6
/// proto:		xor lhs, rhs, dst
/// descript:	Computes (lhs ^ rhs) and stores the result in register dst. Result affects zf.

#include "vm.h"

static void	vm_mem_read_from_offset(t_byte *dst, t_mem *src, t_size offset, t_size mem_size)
{
	t_size	i;

	i = 0;
	while (i < offset)
	{
		dst[i] = src->mem[offset];
		offset = (offset + i) % mem_size;
		i++;
	}
}

static t_int32	vm_get_param(t_int32 *param, t_arena *a, t_process *p, int index)
{
	t_uint8	reg_addr;
	t_int16	ind_offset;

	if (p->current_instruction.args[index].type == REG_CODE)
	{
		vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[index].data);
		if (reg_addr > 16)
		{
			print("reg addr > 16\n");
			return (0);
		}
		vm_reg_store((t_byte *)&param, &p->registers[reg_addr - 1]);
	}
	else if (p->current_instruction.args[index].type == DIR_CODE)
		vm_reg_store((t_byte *)&param, &p->current_instruction.args[index].data);
	else
	{
		vm_reg_store((t_byte *)&ind_offset, &p->current_instruction.args[index].data);
		vm_mem_read_from_offset((t_byte *)&param, &a->mem, p->pc + ind_offset, MEM_SIZE);
	}
	return (1);
}

void	vm_instr_xor(t_arena *a, t_process *p)
{
	t_int32	lhs;
	t_int32	rhs;
	t_int32	result;
	t_uint8	reg_addr;

	// Get lhs, rhs
	if (!vm_get_param(&lhs, a, p, 0))
		return ;
	if (!vm_get_param(&rhs, a, p, 1))
		return ;

	// Calculate result(lhs ^ rhs)
	result = lhs ^ rhs;

	// Update zf
	p->zf = (result == 0);

	// Get result register address
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[2].data);
	if (reg_addr > 16)
		return ;

	// Store result in register
	vm_reg_load(&p->registers[reg_addr - 1], (t_byte *)&result);
}
