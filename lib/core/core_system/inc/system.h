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

#ifndef SYSTEM_H
# define SYSTEM_H

# include "../../core_containers/parray/inc/parr.h"
# include "../../inc/types.h"

typedef struct s_file_pos
{
	const char	*func;
	char		*file;
	t_size		line;
}				t_file_pos;

void		cr_error(t_file_pos *err_pos, char *message);
void		cr_debug(t_file_pos *file_pos, t_size count, ...);
void		cr_activate(void);
void		cr_deactivate(void);
void		cr_log(void);
t_parray	cr_stacktrace(t_size offset);

#endif
