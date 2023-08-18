.text
.global _start
.org 	0x0000

_start:
IF:
	ldw 	r2, X(r0)
	subi	r2, r2, 3
	ldw 	r3, Y(r0)
	bge 	r3, r2, ELSE
THEN: 
	addi 	r3, r3, 2
	stw 	r3, Y(r0)
	br 	END_IF
ELSE:
	ldw 	r4, Z(r0)
	stw 	r4, Y(r0)
END_IF:
	ldw 	r4, Z(r0)
	subi 	r4, r2, 5
	stw 	r4, Z(r0)
	break
	
	.org 	0x1000
X: 	.word 	7 
Y: 	.word 	4
Z: 	.word	9

	.end
	
	