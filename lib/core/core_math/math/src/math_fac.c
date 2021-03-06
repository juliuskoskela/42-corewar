/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_fac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoskela <jkoskela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 02:10:04 by jkoskela          #+#    #+#             */
/*   Updated: 2021/05/20 21:57:40 by jkoskela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/core.h"

t_int64	math_fac(t_int64 n)
{
	t_int64		i;
	t_int64		fac;

	i = 1;
	fac = 1;
	while (i <= n)
	{
		fac = fac * i;
		i++;
	}
	return (fac);
}

/*
**  ----------------------------------------------------------------------------
**
**	math_fac
**
**	Calculate the factorial of n.
**
**  ----------------------------------------------------------------------------
*/
