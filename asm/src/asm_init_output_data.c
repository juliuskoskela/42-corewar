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

#include "asm.h"

void	asm_init_output_data(t_output_data *data, int verbose)
{
	mset(data, 0, sizeof(*data));
	data->program = (int8_t *)malloc(sizeof(int8_t) * CHAMP_MAX_SIZE);
	if (data->program == NULL)
		asm_exit_error("Malloc error on allocating program data");
	mset(data->program, 0, CHAMP_MAX_SIZE);
	data->program_capacity = CHAMP_MAX_SIZE;
	data->header.magic = COREWAR_EXEC_MAGIC;
	data->verbose = verbose;
}
