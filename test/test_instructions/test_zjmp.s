.name "TEST_ZJMP"
.comment "test jumping"

# zjmp offset

# Moves the process's PC by offset only if the
# process's zf is set to 1

# x cycles

# { T_DIR }

jump_above:

zjmp %:jump_down

ld %0, r5

zjmp %1

ld %5, r5

jump_loop: 
sub r5, %1, r5
zjmp %:jump_loop

zjmp %:jump_above

jump_down: zjmp %0

zjmp %-500
zjmp %5000
zjmp %-5000
