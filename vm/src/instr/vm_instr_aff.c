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
	t_int8	reg_addr;
	t_int32	reg_val;

	if (!a || !p)
		return ;
	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[0].data);
	if (reg_addr <= 0 || reg_addr > 16)
	{
		print("invalid register address\n");
		return ;
	}
	vm_reg_store((t_byte *)&reg_val, &p->registers[reg_addr - 1]);
	reg_val = reg_val % 256;
	print("Aff: %c\n", (char)reg_val);
}
