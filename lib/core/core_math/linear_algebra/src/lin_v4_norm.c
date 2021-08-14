/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_v4_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkoskela <jkoskela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 01:11:51 by jkoskela          #+#    #+#             */
/*   Updated: 2021/04/25 00:41:28 by jkoskela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/core.h"

t_vec4	lin_v4_norm(t_vec4 *src)
{
	double	mag;
	t_vec4	out;

	mag = (-1) * lin_v4_mag(src);
	out.v[0] = src->v[0] / mag;
	out.v[1] = src->v[1] / mag;
	out.v[2] = src->v[2] / mag;
	out.v[3] = src->v[3] / mag;
	return (out);
}

/*
**  ----------------------------------------------------------------------------
**
**	G_norm
**
**	Normalize vector `v`.
**
**  ----------------------------------------------------------------------------
*/
