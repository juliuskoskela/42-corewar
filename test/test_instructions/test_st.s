.name "TEST_ST"
.comment "TESTING ST"

# st src, dst

# Stores the value of registry src in dst

# 5 cycles

# { T_REG, T_IND | T_REG }

l2:		st r1, :live

st r1, 100
st r16, 200

st r1, 0

st r10, r12
st r2, r2
st r1, r16
st r1, r15

st r1, :l2

st r1, -100
st r10, -1

live:	live %1


