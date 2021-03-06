#include "asm.h"

static int	asm_get_decimal(int32_t *dst, char *str)
{
	int32_t	value;
	int32_t	sign;

	value = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (is_digit(*str))
	{
		value = value * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		return (0);
	*dst = sign * value;
	return (1);
}

static int	asm_get_hex(int32_t *dst, char *str)
{
	static const char	digits[17] = "0123456789abcdef";
	int32_t				value;
	int32_t				i;

	str += 2;
	while (is_digit(*str) || (*str >= 'a' && *str <= 'f'))
	{
		i = 0;
		while (digits[i] != *str)
			i++;
		value = value * 16 + i;
		str++;
	}
	if (*str != '\0')
		return (0);
	*dst = value;
	return (1);
}

int	asm_get_numeric_value(int32_t *dst, char *str)
{
	if (s_ncmp(str, "0x", 2) == 0)
		return (asm_get_hex(dst, str));
	else
		return (asm_get_decimal(dst, str));
}
