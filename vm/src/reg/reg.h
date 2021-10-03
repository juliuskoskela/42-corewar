#ifndef REG_H
# define REG_H

# include "vm.h"

typedef struct s_reg t_reg;

void	vm_reg_copy(t_reg *dst, t_reg *src);
void	vm_reg_deref(t_byte *dst, t_reg *src);
void	vm_reg_print(t_reg *src);
void	vm_reg_ref(t_reg *dst, t_byte *src);
t_reg	*vm_reg_set(t_reg *src, t_size len);

#endif
