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
#include "core.h"

static void	asm_resize_program(t_output_data *data)
{
	int		new_capacity;
	int8_t	*new_program;

	new_capacity = data->program_capacity * 2;
	new_program = (int8_t *)malloc(sizeof(int8_t) * new_capacity);
	if (new_program == NULL)
		asm_exit_error("Malloc error on reallocating program data");
	mcpy(new_program, data->program, data->program_capacity);
	free(data->program);
	data->program = new_program;
	data->program_capacity = new_capacity;
}

void	asm_write_bytes(t_output_data *data, uint32_t *lc, void *bytes, int n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		if (*lc == data->program_capacity)
			asm_resize_program(data);
		data->program[*lc] = ((int8_t *)bytes)[i];
		*lc = *lc + 1;
		i--;
	}
}
