/// opcode:		16 (0x10)
/// mnemonic:	aff
/// name:		aff
/// params:		1 : { T_REG }
/// acb:		true
/// ncycles:	2
/// proto:		aff chr
/// descript:	Makes this process' champion talk by displaying chr's value. This instruction is useful if you want to ridicule your opponents.

#include "vm.h"

void	vm_instr_aff(t_arena *a, t_process *p)
{
	t_uint8	reg_addr;
	t_int32	reg_val;

	if (!a)
		return ;
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[0].data);
	if (reg_addr > 16)
	{
		print("reg addr > 16\n");
		return ;
	}
	vm_reg_store((t_byte *)&reg_val, &p->registers[reg_addr - 1]);
	print("%c", (char)reg_val);
}
