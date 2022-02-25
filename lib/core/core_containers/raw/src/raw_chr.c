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

t_hraw	raw_chr(t_raw src, t_raw b)
{
	t_hraw	res;
	t_size	i;

	res.data = NULL;
	res.size = 0;
	i = 0;
	while (i < src.size)
	{
		if (mcmp(&src.data[i], b.data, b.size) == 0)
		{
			res = hraw_range(src, i, src.size);
			return (res);
		}
		i++;
	}
	return (res);
}
