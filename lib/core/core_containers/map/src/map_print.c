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

#include "../inc/map.h"
#include "../../../inc/core.h"

void	map_print(t_map *m)
{
	t_size	i;

	i = 0;
	while (i < m->capacity)
	{
		if (map_null_node(&m->node[i]))
			print("[EMPTY]\n");
		else
			print("%s\n", m->node[i].key);
		i++;
	}
}
