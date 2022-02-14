.name "TEST_ST"
.comment "TESTING ST"

# st src, dst

# Stores the value of registry src in dst

# x cycles

# { T_REG, T_IND | T_REG }

l2:		st r1, :live

st r1, 100
st r16, 2
st r10, r1
st r2, r2

live:	live %1
