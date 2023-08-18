PrintHexByte:
	subi	sp, sp ,12
	stw	ra, 8(sp)
	stw	r3, 4(sp)
	stw	r2, 0(sp)

	mov 	r3, r2
	srli 	r2, r2, 4
	call	PrintHexDigit

	andi 	r2, r3, 0xF
	call 	PrintHexDigit

	ldw	ra, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi 	sp, sp, 12
	
	ret