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

static double	_str_tof_sub(const char *str, double res)
{
	int			decimal;

	decimal = 0;
	while (is_digit(*str) == 1 && *str != '.')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	str++;
	if (*str == '\0')
		return (res);
	while (is_digit(*str) == 1)
	{
		res = res * 10 + (*str - 48);
		str++;
		decimal++;
	}
	while (decimal--)
		res = res / 10;
	return (res);
}

double	str_tof(const t_str str)
{
	const char	*ptr;
	double		res;
	double		negative;

	ptr = (const char *)str.raw.data;
	negative = 1;
	res = 0;
	while (is_wspace(*ptr) == 1)
		ptr++;
	if (*ptr == '-')
		negative = -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	res = _str_tof_sub(ptr, res);
	return (res * negative);
}
