PrintHexDigit:
	subi	sp, sp, 12
	stw 	ra, 8(sp)
	stw	r3, 4(sp)
	stw 	r2, 0(sp)
phd_if:
	movi	r3, 10 
	bge	r2, r3, phd_else

phd_then:
	addi 	r2, r2, 0
	br	phd_elseif

phd_else:
	subi 	r2, r2, 10
	addi	r2, r2, 'A'

phd_end_if:
	call PrintChar

	ldw 	ra, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi	sp, sp, 12
	ret