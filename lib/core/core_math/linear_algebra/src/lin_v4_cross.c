/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_v4_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoskela <jkoskela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 00:30:42 by jkoskela          #+#    #+#             */
/*   Updated: 2021/04/25 00:18:22 by jkoskela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/core.h"

t_vec4	lin_v4_cross(t_vec4 *a, t_vec4 *b)
{
	t_vec4	out;

	out.v[0] = (a->v[1] * b->v[2]) - (a->v[2] * b->v[1]);
	out.v[1] = (a->v[2] * b->v[0]) - (a->v[0] * b->v[2]);
	out.v[2] = (a->v[0] * b->v[1]) - (a->v[1] * b->v[0]);
	out.v[3] = 1;
	return (out);
}
/*
**  ----------------------------------------------------------------------------
**
**	Get the cross product of `a` x `b`.
**
**  ----------------------------------------------------------------------------
*/
