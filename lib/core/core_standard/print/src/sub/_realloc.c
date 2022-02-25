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
 * \authors Satu Koskinen
 *
 * \brief
 *
 *****************************************************************************/

#include "../../../inc/core.h"
#include "../inc/print_internal.h"

void	*_realloc(void *ptr, t_size old_size, t_size new_size)
{
	void	*new;
	t_size	copy_size;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		new = NULL;
	}
	else
		new = (void *)malloc(new_size);
	if (new != NULL && ptr != NULL)
	{
		if (new_size < old_size)
			copy_size = new_size;
		else
			copy_size = old_size;
		mcpy(new, ptr, copy_size);
		if (new_size > old_size)
			mset((void *)(&((char *)new)[old_size]),
				0, new_size - old_size);
		free(ptr);
	}
	return (new);
}
