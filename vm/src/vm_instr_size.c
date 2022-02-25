/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:12:07 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:12:08 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_size	vm_instr_size(t_instr *src)
{
	return (
		sizeof(src->opcode)
		+ (t_size)src->op->has_argument_coding_byte
		+ src->args[0].data.len
		+ src->args[1].data.len
		+ src->args[2].data.len);
}
