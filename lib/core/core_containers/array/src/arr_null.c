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
/// \brief Checks if the array is a null array.
///
/// \param src The source array.
///
/// \return 1 on success 0 on failure.
///
///////////////////////////////////////////////////////////////////////////////

#include "../inc/array.h"

t_ssize	arr_null(t_array *src)
{
	if (src->raw.data == NULL)
		return (CR_SUCCESS);
	return (CR_FAIL);
}
