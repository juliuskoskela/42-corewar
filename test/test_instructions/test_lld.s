.name "TEST_LLD"
.comment "loadety loadety LONG load"

# lld src, dst

# Long version of ld
# Loads src in register dst, value of src affects zf

# x cycles

# { T_DIR | T_IND, T_REG }

lld %666, r2
lld %42, r3
lld %-34324, r4

lld 5, r5
lld -10, r6
lld 3543434, r7

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
