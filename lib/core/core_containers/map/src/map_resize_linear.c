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

t_uint64	map_resize_linear(t_uint64 capacity)
{
	return (capacity * 2);
}
