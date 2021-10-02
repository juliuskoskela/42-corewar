#include "../inc/vm_2.h"

void	mem_increment_pos(t_mem *src, t_size i)
{
	src->pos = (src->pos + i) % src->len;
}
