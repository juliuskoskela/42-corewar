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

void	str_rev(t_str *src)
{
	t_size	half;
	t_size	i;
	t_size	j;

	half = src->len / 2;
	i = 0;
	j = src->len - 1;
	while (i < half)
	{
		mswap(&src->raw.data[i], &src->raw.data[j], sizeof(char));
		i++;
		j--;
	}
}
