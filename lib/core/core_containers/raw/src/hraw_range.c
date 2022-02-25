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

#include "../../../inc/core.h"

t_hraw	hraw_range(t_raw src, t_size s, t_size t)
{
	t_hraw	new;

	new.data = NULL;
	new.size = 0;
	if (s > src.size || s > t)
		return (new);
	else if (t > src.size)
		t = src.size;
	new.data = src.data;
	new.data += s;
	new.size = t - s;
	return (new);
}
