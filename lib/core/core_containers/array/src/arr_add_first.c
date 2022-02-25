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
/// \brief Add a new element to the beginning of a dynamic array.
///
/// If the array is not sufficiently big a new memory area double the
/// alloc_size of the previous one is allocated.
///
/// \param dst Destination array.
/// \param elem Element to be added.
/// \return 1 on success 0 on failure.
///
///////////////////////////////////////////////////////////////////////////////

#include "../inc/array.h"

t_ssize	arr_add_first(t_array *dst, void *elem)
{
	if (!(arr_add(dst, elem, 0)))
		return (CR_FAIL);
	return (CR_SUCCESS);
}
