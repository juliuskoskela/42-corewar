.name "st_tester"
.comment "TESTING ST"

l2:		st r1, :live
		and r1, %:end, r1

live:	live %1
		zjmp %:live

end:
