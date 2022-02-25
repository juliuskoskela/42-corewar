/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:11:10 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:11:11 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_process_debug(char *msg, int verbosity)
{
	if (verbosity & VM_VERBOSE_OPS)
		print("%s\n", msg);
}
