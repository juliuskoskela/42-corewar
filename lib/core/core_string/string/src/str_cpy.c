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

#include "../inc/string.h"

t_str	str_cpy(t_str dst, t_str src)
{
	if (dst.raw.size < src.len)
		raw_realloc(&dst.raw, src.len);
	raw_cpy(dst.raw, src.raw, src.len);
	dst.len = src.len;
	dst.raw.data[dst.len] = '\0';
	return (dst);
}
