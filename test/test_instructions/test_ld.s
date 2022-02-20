# ld T_DIR src, T_IND, T_REG dst
# Loads src in register dst, value of src affects zf
# 5 cycles

.name "TEST_LD"
.comment "Tests ld"

ld %666, r2
ld %42, r3
ld %-34324, r4

ld -10, r5
ld 3543434, r6
