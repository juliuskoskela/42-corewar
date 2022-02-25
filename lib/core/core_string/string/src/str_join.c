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

t_str	str_join(t_str dst, t_str src)
{
	t_hraw	raw_ptr;

	if (dst.raw.size < dst.len + src.len)
		raw_realloc(&dst.raw, (dst.len + src.len) * 3);
	raw_ptr = hraw_range(dst.raw, dst.len, src.len + dst.len);
	raw_cpy(raw_ptr, src.raw, src.len);
	dst.len = dst.len + src.len;
	dst.raw.data[dst.len] = '\0';
	return (dst);
}
