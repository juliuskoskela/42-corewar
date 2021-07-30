#include "asm.h"

void	asm_write_bytes(int8_t *program, uint32_t *lc, void *bytes, int n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		if (*lc == CHAMP_MAX_SIZE)
			asm_exit_error("Program too large");
		program[*lc] = ((int8_t *)bytes)[i];
		*lc = *lc + 1;
		i--;
	}
}
