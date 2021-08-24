.name "TEST_STI"
.comment "TESTING STI"

# sti src, lhs, rhs

# Computer lhs + rhs and uses the result as an offset
# to address memory and store the value of register src
# at that memory location

# x cycles

# { T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG }
