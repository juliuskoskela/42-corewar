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

///////////////////////////////////////////////////////////////////////////////
///
/// \authors Julius Koskela
///
/// \brief Take the first element from an array.
///
/// Take is a combination of get and del. A pointer to an allocated memory dst
/// sufficient to hold the results has to be passed as a parameter.
///
/// \param dst Destination memory.
/// \param src source array.
///
/// \return Pointer to dst.
///
///////////////////////////////////////////////////////////////////////////////

#include "../inc/array.h"

void	*arr_take_first(void *dst, t_array *src)
{
	dst = arr_take(dst, src, 0);
	return (dst);
}
