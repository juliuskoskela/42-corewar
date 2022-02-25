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

#include "../../inc/core.h"
#include "../inc/system_internal.h"

void	cr_activate(void)
{
	t_core	*core;

	core = cr_static();
	core->active = TRUE;
	core->track_errors = CR_TRACK_ERROR;
	core->track_errors_backtrace = CR_TRACK_ERROR_BACKTRACE;
	core->track_allocs = CR_TRACK_ALLOC;
	core->track_allocs_backtrace = CR_TRACK_ALLOC_BACKTRACE;
	if (core->track_errors == TRUE)
		core->errors = parr_new(1);
	if (core->track_allocs == TRUE)
		core->allocs = parr_new(1);
	print("\n\033[32;1mCORE SYSTEM\033[0m\n\n");
	print("Active!.\n\n");
}
