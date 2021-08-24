.name "TEST_LDI"
.comment "loadety loadety load INDEX"

# ldi lhs, rhs, dst

# Computer lhs + rhs and uses the result as an offset to address memory
# and load a 32-bit value into the register dst

# x cycles

# { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }

