.name "ZORK BEATER"
.comment "i'm here just to bring that one process down, and to live to see it"

; first, execute a valid live

start:	sti r1, %:live, %1
		and r1, %0, r2
live:	live %1

; fork a process that start forking other processes
; to execute the second live loop

fork %:fork0

; our basic living loop

store_pid:	sti r1, %:live_loop, %1
			and r1, %0, r2

live_loop:	live %1
			zjmp %:live

; first forked process will set the correct
; id for our live_2 where the next forked
; processes will jump right to

fork_beginning:
		sti r1, %:live_2, %1
		and r1, %0, r2

live_2: live %1
		zjmp %:live_2

		sti r1, %:live_3, %1
		and r1, %0, r2

live_3: live %1
		zjmp %:live_3

fork0:	fork %:fork_beginning
fork1:	fork %:live_2
fork2:	fork %:live_2
fork3:	fork %:live_2
fork4:	fork %:live_2
fork5:	fork %:live_2
fork6:	fork %:live_2
fork7:	fork %:live_2
fork8:	fork %:live_2
fork9:	fork %:live_2
fork10:	fork %:live_2
fork11:	fork %:live_2
fork12:	fork %:live_2
fork13:	fork %:live_2
fork14:	fork %:live_2
fork15:	fork %:live_2
fork16:	fork %:live_2
fork17:	fork %:live_2
fork18:	fork %:live_2
fork19:	fork %:live_2
fork20:	fork %:live_2

zjmp %:fork1
