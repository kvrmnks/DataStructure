load R1,[A]
load R2,[B]
load R3,[C]
load R5, 0
load R6, 2
loop:
move R0, R2
jmpLE R1<=R0, swap0
move R4, R1
move R1, R2
move R2, R4

swap0:
move R0, R3
jmpLE R2<=R0, swap1
move R4, R2
move R2, R3
move R3, R4
swap1:

load R7, 1
addi R5, R5, R7
move R0, R5
jmpEQ R6=R0, exit
jmp loop
exit:
load R4, A
load R5, B
load R6, C
store R1, [R4]
store R2, [R5]
store R3, [R6]
halt
org 0xf0
A:
db 9
org 0xf1
B:
db 5
org 0xf2
C:
db 1
