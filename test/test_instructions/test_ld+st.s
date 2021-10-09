# ld T_DIR src, T_IND, T_REG dst
# Loads src in register dst, value of src affects zf
# 5 cycles

.name "TEST_LD"
.comment "Fill registers 1 - 16 with numbers 1 - 16"

ld %666, r2
st r2, 42
