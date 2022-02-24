# ld T_DIR src, T_IND, T_REG dst
# Loads src in register dst, value of src affects zf
# 5 cycles

.name "TEST_LD"
.comment "Tests ld"

ld %516, r2
st r2, 516
zjmp %516
ldi %258, %258, r2
sti r2, %258, %258
fork %516 
