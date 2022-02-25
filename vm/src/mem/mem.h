/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satukoskinen <satukoskinen@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:13:31 by satukoskine       #+#    #+#             */
/*   Updated: 2022/02/25 20:13:31 by satukoskine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "core.h"

typedef struct s_mem
{
	t_byte		*mem;
	t_size		pos;
	t_size		len;
}	t_mem;

// A memory object `t_mem` keeps record of an internal read position.
// Reading and writing from memory increment the read position automatically.

// Allocate new memory
t_mem	*vm_mem_new(t_mem *src, t_size len);

// Free memory `src`
void	vm_mem_free(t_mem *src);

// Read `nbytes` from the current position in `src`to `dst`.
// Position is automatically incremented by the amount of bytes
// read or written.
t_bool	vm_mem_read(t_byte *dst, t_mem *src, size_t nbytes);

// Write `nbytes` from the start of `src`  into the memory `dst`
t_bool	vm_mem_write(t_mem *dst, t_byte *src, size_t nbytes);

// Increment memory position manually. Normally the position
// will be automatically incremented by `vm_mem_read` and
// `vm_mem_write`
void	vm_mem_increment_pos(t_mem *src, t_size i);

// Set read position manually.
t_mem	*vm_mem_set_pos(t_mem *src, t_size pos);

// Increment read position.
void	vm_mem_increment_pos(t_mem *src, t_size i);

// Printing
void	vm_mem_print(t_mem *src);

// Print start + len characters with a colour
void	vm_mem_print_overlay(t_mem *src, t_size start,
			t_size len, char *colour);

#endif
