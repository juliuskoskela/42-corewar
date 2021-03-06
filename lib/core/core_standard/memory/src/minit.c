/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoskela <jkoskela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:30:56 by jkoskela          #+#    #+#             */
/*   Updated: 2021/05/19 04:25:36 by jkoskela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/core.h"

void	*minit(t_size size)
{
	void	*p;

	p = malloc(size);
	if (p)
		mzero(p, size);
	return (p);
}

/*
**  ----------------------------------------------------------------------------
**
**	minit
**
**	Void memory allocation; allocates `size` bytes of memory and initializes
**	the memory.
**
**  ----------------------------------------------------------------------------
*/
