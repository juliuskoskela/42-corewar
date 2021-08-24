.name "TEST_LLDI"
.comment "loadety loadety load LONG!!!! INDEX"

# lldi lhs, rhs, dst

# Long version of ldi, neither parameter values nor computed address
# will have their reach limited
# Value loaded from memory affects zf
# Computer lhs + rhs and uses the result as an offset to address memory
# and load a 32-bit value into the register dst

# x cycles

# { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }

