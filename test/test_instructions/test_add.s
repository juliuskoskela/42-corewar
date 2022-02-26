.name "TEST_ADD"
.comment "test add instruction!!!!!"

# add lhs, rhs, dst

# Computes lhs + rhs and stores the result in register dst
# Result affects zf

# x cycles

# { T_REG, T_REG, T_REG }

ld %42, r2
ld %-500, r3
ld %4096, r4
ld %-1, r5
ld %2, r6

add r2, r4, r10
add r1, r1, r1
add r10, r15, r16
add r5, r6, r10
add r3, r5, r3
add r3, r12, r1

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
