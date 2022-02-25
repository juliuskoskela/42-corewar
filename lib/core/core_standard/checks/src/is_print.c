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
 * \brief Returns 1 if `c` is a printable character.
 *
 *****************************************************************************/

#include "../../../inc/core.h"

int	is_print(int c)
{
	if (c >= 32 && c <= 126)
		return (CR_TRUE);
	return (CR_FALSE);
}
