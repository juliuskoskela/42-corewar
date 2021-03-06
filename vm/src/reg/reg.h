#ifndef REG_H
# define REG_H

# include "vm.h"

typedef struct s_reg t_reg;

// Copy contents from src to dst
void	vm_reg_copy(t_reg *dst, t_reg *src);

// Set the size of the register (smaller then REG_SIZE)
t_reg	*vm_reg_set_size(t_reg *src, t_size len);

// Store a value from register `src` into memory pointed
// by `dst`
void	vm_reg_store(t_byte *dst, t_reg *src);

// Load a value from memory pointed to by `src`into the register
// dst. Register will determine how many bytes are copied
void	vm_reg_load(t_reg *dst, t_byte *src);

// Print a register.
void	vm_reg_print(t_reg *src);

#endif
