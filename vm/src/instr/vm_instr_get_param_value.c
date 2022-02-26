/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_get_param_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:14:30 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:14:31 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_parameter_value(t_int32 param)
{
	size_t	i;

	print(" => value: %d", param);
	print(" [");
	i = 0;
	while (i < 4)
	{
		print("%02x", ((t_byte *)&param)[i]);
		if (i < 3)
			print(" ");
		i++;
	}
	print("]\n");
}

static void	get_indirect_value(t_int32 *param,
t_arena *a, t_process *p, int index)
{
	t_int16	ind_offset;

	vm_reg_store((t_byte *)&ind_offset,
		&p->current_instruction.args[index].data);
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => indirect offset: %d", ind_offset);
	vm_mem_set_pos(&a->mem, (t_size)((int)p->pc + ind_offset));
	vm_mem_read((t_byte *)param, &a->mem, REG_SIZE);
	if (ENDIAN_BIG)
		vm_reverse_bytes(param, param, REG_SIZE);
}

static void	get_direct_value(t_int32 *param, t_arena *a, t_process *p,
int index)
{
	t_int16	dir_value;

	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => direct");
	if (p->current_instruction.args[index].data.len == 2)
	{
		vm_reg_store((t_byte *)&dir_value,
			&p->current_instruction.args[index].data);
		*param = (int)dir_value;
	}
	else
	{
		vm_reg_store((t_byte *)param, &p->current_instruction.args[index].data);
	}
}

static t_int32	get_register_value(t_int32 *param,
t_arena *a, t_process *p, int index)
{
	t_int8	reg_addr;

	vm_reg_store((t_byte *)&reg_addr, &p->current_instruction.args[index].data);
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => register: %d", reg_addr);
	if (reg_addr <= 0 || reg_addr > 16)
	{
		vm_process_debug("Invalid register number", a->verbosity);
		return (0);
	}
	vm_reg_store((t_byte *)param, &p->registers[reg_addr - 1]);
	return (1);
}

t_int32	vm_instr_get_param_value(t_int32 *param,
t_arena *a, t_process *p, int index)
{
	*param = 0;
	if (a->verbosity & VM_VERBOSE_OPS)
		print(" => parameter %d", index);
	if (p->current_instruction.args[index].type == REG_CODE)
	{
		if (!get_register_value(param, a, p, index))
			return (0);
	}
	else if (p->current_instruction.args[index].type == DIR_CODE)
		get_direct_value(param, a, p, index);
	else
		get_indirect_value(param, a, p, index);
	if (a->verbosity & VM_VERBOSE_OPS)
		print_parameter_value(*param);
	return (1);
}
