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

char	*map_parse(
	t_map *src,
	void *dst,
	char *(*f)(void *, void *, const char *key))
{
	t_map_node	node;
	t_size		i;

	node = (t_map_node){NULL, NULL};
	i = 0;
	while (i < src->capacity)
	{
		if (!map_null_node(&src->node[i]))
		{
			node = src->node[i];
			if (!(f(dst, node.data, node.key)))
				return ((char *)node.key);
		}
		i++;
	}
	return ((char *)node.key);
}
