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

t_str	str_ncpy(t_str dst, t_str src, t_size len)
{
	if (dst.raw.size < len)
		raw_realloc(&dst.raw, src.len);
	if (src.len < len)
		len = src.len;
	raw_cpy(dst.raw, src.raw, len);
	dst.len = len;
	dst.raw.data[len] = '\0';
	return (dst);
}
