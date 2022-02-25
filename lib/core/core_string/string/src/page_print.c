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

static t_ssize	print_str(void *data, t_size i)
{
	t_str	*ptr;

	ptr = data;
	str_write(*ptr);
	if (!(write(1, "\n", 1)))
		return (CR_STOP);
	return (i);
}

void	page_print(t_page p)
{
	arr_iter(&p, print_str);
}
