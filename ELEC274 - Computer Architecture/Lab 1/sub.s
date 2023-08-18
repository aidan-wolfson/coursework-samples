.text 
.global _start
.org	0x0000

_start:
	movui	sp, #0x7FFC
	ldw	r2, A(r0)
	ldw	r3, B(r0)
	ldw	r4, C(r0)
	call	Sub1
	stw	r2, RESULT(r0)
	break

Sub1:
	addi 	r2, r2, 7
	sub	r3, r3, r4
	addi	r3, r3, 2
	sub	r2, r2, r3
	ret
	

		.org 	0x1000
RESULT:		.skip	4
A: 		.word 	3 
B: 		.word 	5
C: 		.word	1

	.end