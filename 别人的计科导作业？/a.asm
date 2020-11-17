load R1,[A]
load R2,[B]
load R0,[C]
addi R1,R1,R2
move R8, R0
move R9, R1
jmpEQ R1=R0, equal

positive:
	load R3, 0xff
	xor R3, R3, R0
	load R0, 1
	addi R3, R3, R0
	addi R1, R1, R3
	move R0, R8
	jmpLE R9<=R0, negative
	move R0, R1
	load R1, 10
	jmpLE R1<=R0, warning
	load R1, 48
	addi R0, R1, R0
	move RF, R0
	halt
negative:
	load R3, 0xff
	addi R1, R1, R3
	xor R1, R1, R3
	move R0,R1
	load R1, 10
	jmpLE R1<=R0, warning
	load RF, 45
	load R1, 48
	addi R0, R1, R0
	move RF, R0	
	halt
equal:
	load RF, 48
	halt
warning:
	load R1, Text
	load R2, 1
	load R0, 0
NextChar:load    RF,[R1]     ;get character and print it on screen
         addi    R1,R1,R2    ;increase address
         jmpEQ   RF=R0,Ready ;when string-terminator, then ready
         jmp     NextChar    ;next character
Ready:   halt
	halt
Text:	
	db 10
	db "answer is not",10
	db "single digit",10
	db 0
org 0xf0
A:
db 16
org 0xf1
B:
db 14
org 0xf2
C:
db 39
