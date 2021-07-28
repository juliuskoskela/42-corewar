#include "argparser.h"
#include <string.h>

const t_argparser_option	*_argparser_get_option(char *argument,
const t_argparser_option *options, int long_option)
{
	size_t	i;
	size_t	arg_len;

	arg_len = strlen(argument);
	if (arg_len == 0 || (long_option == 0 && arg_len > 1))
		return (NULL);
	i = 0;
	while (options[i].name != NULL)
	{
		if (long_option)
		{
			if (strcmp(argument, options[i].name) == 0)
				return (&options[i]);
		}
		else
		{
			if (argument[0] == (char)options[i].key)
				return (&options[i]);
		}
		i++;
	}
	return (NULL);
}
