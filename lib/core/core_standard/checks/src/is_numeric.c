/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a header                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************
 *
 * \authors Julius Koskela
 *
 * \brief Returns 1 if `c` is a numeric character.
 *
 *****************************************************************************/

#include "../../../inc/core.h"

int	is_numeric(int c)
{
	if (s_chr("0123456789+-.", c))
		return (CR_TRUE);
	return (CR_FALSE);
}
