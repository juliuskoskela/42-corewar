#ifndef MEM_H
# define MEM_H

# include "core.h"

typedef struct s_mem
{
	t_byte		*mem;
	t_size		pos;
	t_size		len;
}	t_mem;

void	vm_mem_free(t_mem *src);
void	vm_mem_increment_pos(t_mem *src, t_size i);
t_mem	*vm_mem_new(t_mem *src, t_size len);
void	vm_mem_print_overlay(t_mem *src, t_size start, t_size len, char *colour);
void	vm_mem_print(t_mem *src);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);
t_mem	*vm_mem_set(t_mem *src, t_size pos);
t_bool	vm_mem_write(t_mem *dst, t_byte *src, size_t src_len);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);
void	vm_mem_increment_pos(t_mem *src, t_size i);
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t dst_len);

#endif
