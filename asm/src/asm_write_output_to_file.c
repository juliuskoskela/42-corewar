#include "asm.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	asm_write_bytes_to_file(int fd, void *bytes, int n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		write(fd, &((int8_t *)bytes)[i], 1);
		i--;
	}
}

static void	asm_write_header_to_file(int fd, t_header header)
{
	if (ASM_PRINT_DEBUG)
		printf("write magic %u : %#x\n", header.magic, header.magic);
	asm_write_bytes_to_file(fd, &header.magic, sizeof(header.magic));
	if (ASM_PRINT_DEBUG)
		printf("write prog_name '%s'\n", header.prog_name);
	write(fd, header.prog_name, sizeof(header.prog_name));
	if (ASM_PRINT_DEBUG)
		printf("write prog_size %u : %#x\n", header.prog_size, header.prog_size);
	asm_write_bytes_to_file(fd, &header.prog_size, sizeof(header.prog_size));
	if (ASM_PRINT_DEBUG)
		printf("write comment '%s'\n", header.comment);
	write(fd, header.comment, sizeof(header.comment));
}

static void	asm_write_program_to_file(int fd, int8_t *program, t_header header)
{
	if (ASM_PRINT_DEBUG)
		printf("write program of size %u\n", header.prog_size);
	write(fd, program, header.prog_size);
}

static char	*asm_get_output_path(char *path)
{
	char	*cor_file;
	size_t	path_len;
	size_t	file_name_len;

	path_len = strlen(path);
	file_name_len = path_len + 2;
	cor_file = (char *)malloc(sizeof(char) * (file_name_len + 1));
	if (cor_file == NULL)
		asm_exit_error("Malloc error in allocating output file name");
	strcpy(cor_file, path);
	strcpy(&cor_file[path_len - 1], "cor");
	return (cor_file);
}

void	asm_write_output_to_file(char *path, t_output_data data)
{
	char	*cor_file;
	int		fd;

	cor_file = asm_get_output_path(path);
	fd = open(cor_file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		asm_exit_error("Error on writing output to .cor file");
	printf("Writing output to %s\n", cor_file);
	free(cor_file);
	asm_write_header_to_file(fd, data.header);
	asm_write_program_to_file(fd, data.program, data.header);
	close(fd);
}

