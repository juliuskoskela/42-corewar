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

t_ssize	raw_realloc(t_raw *m, t_size new_size)
{
	t_raw	new;

	new = raw_new(new_size);
	if (new_size < m->size)
		mcpy(new.data, m->data, new_size);
	else
		mcpy(new.data, m->data, m->size);
	raw_free(m);
	*m = new;
	return (new.size);
}
