# ld T_DIR | T_IND src, T_REG dst
# Loads src in register dst, value of src affects zf
# 5 cycles

.name "TEST_LD"
.comment "Tests ld"

ld %666, r2
ld %42, r3
ld %-34324, r4

ld 5, r5
ld -10, r6
ld 3543434, r7

st r1, 100
st r2, 100
st r3, 100
st r4, 100
st r5, 100
st r6, 100
st r7, 100
st r8, 100
st r9, 100
st r10, 100
st r11, 100
st r12, 100
st r13, 100
st r14, 100
st r15, 100
st r16, 100
