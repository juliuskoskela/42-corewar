.name "TEST_LDI"
.comment "loadety loadety load INDEX"

# ldi lhs, rhs, dst

# Computer lhs + rhs and uses the result as an offset to address memory
# and load a 32-bit value into the register dst

# x cycles

# { T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG }

ldi %666, r1, r2
ldi %42, r2, r3
ldi %-34324, r4, r4

ldi 5, %5, r10
ldi %5, %0, r11
ldi -10, %-10, r5
ldi 3543434, %100, r6

ldi r1, r2, r3

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
