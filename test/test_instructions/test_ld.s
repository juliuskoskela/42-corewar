.name "TEST_LD"
.comment "loadety loadety load"

# ld src, dst

# Loads src in register dst, value of src affects zf

# x cycles

# { T_DIR | T_IND, T_REG }

load: ld 5, r11
ld 0, r12
