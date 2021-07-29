#include "asm.h"
#include "core.h"
#include <ctype.h>

void	asm_print_char_row(unsigned char *row, int col)
{
	int	i;

	print("  ");
	i = 0;
	while (i < col)
	{
		if (isprint(row[i]))
			print("%c", row[i]);
		else
			print(".");
		i++;
	}
	print("\n");
}

void	asm_print_last_char_row(unsigned char *row, int col)
{
	int	i;

	i = col;
	while (i++ < 16)
		print("   ");
	asm_print_char_row(row, col);
}

void	asm_print_hex(unsigned char byte)
{
	print("%.2x ", byte);
}

void	asm_print_hexdump_bytes(void *bytes, int n, int reverse)
{
	static int				col;
	static unsigned char	row[16];
	int						i;
	int						index;

	if (bytes == NULL)
		asm_print_last_char_row(row, col);
	i = 0;
	while (i < n)
	{
		if (reverse)
			index = n - i - 1;
		else
			index = i;
		asm_print_hex(((unsigned char *)bytes)[index]);
		row[col] = ((unsigned char *)bytes)[index];
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
	t_header	header;

	header = data.header;
	print("Hex dump of output:\n");
	asm_print_hexdump_bytes(&header.magic, sizeof(header.magic), 1);
	asm_print_hexdump_bytes(&header.prog_name, sizeof(header.prog_name), 0);
	asm_print_hexdump_bytes(&header.prog_size, sizeof(header.prog_size), 1);
	asm_print_hexdump_bytes(&header.comment, sizeof(header.comment), 0);
	asm_print_hexdump_bytes(&data.program, header.prog_size, 0);
	asm_print_hexdump_bytes(NULL, 0, 0);
}
