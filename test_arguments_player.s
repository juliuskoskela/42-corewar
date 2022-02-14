.name "argument tester"
.comment "yeah yeah"

ld	%0, r2
sti	r2, %:overwritten, %2

overwritten:
and r1, %:overwritten, r2

sub r1, r1, r1
