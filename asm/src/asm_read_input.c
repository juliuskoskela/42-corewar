#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "core.h"

static int	result_resize(char **result, size_t old_size, size_t new_size)
{
	char	*new_result;

	new_result = (char *)malloc(sizeof(char) * new_size);
	if (new_result == NULL)
	{
		free(*result);
		return (0);
	}
	if (old_size != 0)
		strncpy(new_result, *result, old_size);
	free(*result);
	*result = new_result;
	return (1);
}

static int	result_append(char **result, char *buf, size_t len)
{
	static size_t	current_size;
	static size_t	current_capacity;
	size_t			i;
	size_t			new_size;

	if (len >= current_capacity - current_size)
	{
		new_size = current_capacity * 2 + len + 1;
		if (result_resize(result, current_size, new_size) != 1)
			return (0);
		current_capacity = new_size;
	}
	i = 0;
	while (i < len)
	{
		(*result)[current_size] = buf[i];
		current_size++;
		i++;
	}
	(*result)[current_size] = '\0';
	return (1);
}

void	asm_check_filepath_suffix(const char *filepath)
{
	const char	*suffix;

	suffix = s_rchr(filepath, '.');
	if (suffix == NULL || s_cmp(suffix, ".s") != 0)
		asm_exit_error("Invalid file format, expected a .s file");
}

char	*asm_read_input(const char *filepath)
{
	char	*result;
	char	buf[BUF_SIZE + 1];
	int		fd;
	ssize_t	ret;

	asm_check_filepath_suffix(filepath);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = NULL;
	ret = read(fd, buf, BUF_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (result_append(&result, buf, (size_t)ret) != 1)
			return (NULL);
		ret = read(fd, buf, BUF_SIZE);
	}
	if (ret == -1)
	{
		free(result);
		result = NULL;
	}
	close(fd);
	return (result);
}
