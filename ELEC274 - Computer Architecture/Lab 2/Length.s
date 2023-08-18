PrintString:
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

# questions: how do I return the length value? and did I handle the string pointer correctly?