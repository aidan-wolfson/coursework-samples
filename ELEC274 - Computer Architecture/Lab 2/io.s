PrintChar:
	subi	sp, sp, 8
	stw	r3, 4(sp)
	stw	r4, 0(sp)
	movia	r3, 0x10001000
pc_loop:
	ldwio	r4, 4(r3)
	andhi	r4, r4, 0xFFFF
	beq	r4, r0, pc_loop
	stwio	r2, 0(r3)
	ldw	r3, 4(sp)
	ldw	r4, 0(sp)
	addi	sp, sp, 8
	ret

#------------------------------------------------------------

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

#------------------------------------------------------------

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

#------------------------------------------------------------

PrintString:
	subi 	sp, sp, 12
	stw	ra, 8(sp) 
	stw	r3, 4(sp) #ch
	stw	r2, 0(sp) #str_ptr


ps_loop:
	#ch = read_byte_from address given by str
	ldb 	r3, 0(r2)

ps_if:
	beq 	r3, r0, ps_end_loop	#exit loop if true

ps_end_if:
	call 	PrintChar
	# str_ptr = str_ptr + 1
	addi 	r2, r2, 1
	br	ps_loop

ps_end_loop:
	ldw	ra, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi 	sp, sp, 12
	
	ret

#-------------------------------------------------------------

Length:
	subi 	sp, sp, 12
	stw	ra, 8(sp)
	stw	r3, 4(sp)
	stb	r2, 0(sp)

	movi	r3, 0

ps_loop:
	#ch = read_byte_from address given by str
	movia 	r2, TEXT

ps_if:
	beq 	r2, r0, ps_end_loop	#exit loop if true

ps_end_if:
	# str_ptr = str_ptr + 1
	addi 	r2, r2, 1
	addi	r3, r3, 1
	br	ps_loop

ps_end_loop:
	ldw	ra, 8(sp)
	ldw	r3, 4(sp)
	ldb	r2, 0(sp)
	addi 	sp, sp, 12
	
	ret

