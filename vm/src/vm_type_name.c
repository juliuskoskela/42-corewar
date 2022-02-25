/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_type_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:10:39 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:10:40 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*vm_type_name(t_byte type)
{
	if (type == REG_CODE)
		return ("T_REG");
	else if (type == IND_CODE)
		return ("T_IND");
	else if (type == DIR_CODE)
		return ("T_DIR");
	else
		return ("NULL");
}
