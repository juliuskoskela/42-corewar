/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_instr_print_register.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:15:10 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:15:10 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_instr_print_register(char *str, t_int8 reg_addr, t_process *p)
{
	print(str, reg_addr);
	vm_reg_print(&p->registers[reg_addr - 1]);
	print("\n");
}
