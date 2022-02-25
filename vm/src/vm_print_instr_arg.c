/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_instr_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:33 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:34 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_print_instr_arg(t_arg *arg)
{
	print("%s ", vm_type_name(arg->type));
	vm_reg_print(&arg->data);
}
