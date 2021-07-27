#include "asm.h"
#include <stdio.h>
#include <ctype.h>

void	asm_print_char_row(unsigned char *row, int col)
{
	int	i;

	printf("  ");
	i = 0;
	while (i < col)
	{
		if (isprint(row[i]))
			printf("%c", row[i]);
		else
			printf(".");
		i++;
	}
	printf("\n");
}

void	asm_print_last_char_row(unsigned char *row, int col)
{
	int	i;

	i = col;
	while (i++ < 16)
		printf("   ");
	asm_print_char_row(row, col);
}

void	asm_print_hex(unsigned char byte)
{
	printf("%.2x ", byte);
}

void	asm_print_hexdump_bytes(void *bytes, int n, int reverse)
{
	static int				col;
	static unsigned char	row[16];
	unsigned char			*char_bytes;
	int						i;
	int						index;

	if (bytes == NULL)
		asm_print_last_char_row(row, col);
	char_bytes = (unsigned char *)bytes;
	i = 0;
	while (i < n)
	{
		if (reverse)
			index = n - i - 1;
		else
			index = i;
		asm_print_hex(char_bytes[index]);
		row[col] = char_bytes[index];
		i++;
		col++;
		if (col == 16)
		{
			asm_print_char_row(row, col);
			memset(row, 0, 16);
			col = 0;
		}
	}
}

void	asm_print_output_hexdump(t_output_data data)
{
	printf("Hex dump of output:\n");
	asm_print_hexdump_bytes(&data.header.magic, sizeof(data.header.magic), 1);
	asm_print_hexdump_bytes(&data.header.prog_name, sizeof(data.header.prog_name), 0);
	asm_print_hexdump_bytes(&data.header.prog_size, sizeof(data.header.prog_size), 1);
	asm_print_hexdump_bytes(&data.header.comment, sizeof(data.header.comment), 0);
	asm_print_hexdump_bytes(&data.program, data.header.prog_size, 0);
	asm_print_hexdump_bytes(NULL, 0, 0);
}
