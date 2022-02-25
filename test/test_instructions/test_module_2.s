.name "TEST_MODULE_TWO"
.comment "Tests instructions with value -516"

ld %-516, r2
st r2, -516
zjmp %-516
ldi %-258, %-258, r2
sti r2, %-258, %-258
fork %-516 
live %2
