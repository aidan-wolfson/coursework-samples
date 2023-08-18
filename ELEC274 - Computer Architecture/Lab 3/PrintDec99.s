PrintDec99:
	subi	sp, sp, 24
	stw	ra, 20(sp)
	stw	r6, 16(sp) #constant 10 
	stw	r5, 12(sp) #ones
	stw 	r4, 8(sp) #tens
	stw	r3, 4(sp) #copy of val
	stw	r2, 0(sp) #passed val -> subroutine arguments

	movi 	r6, 10
	mov 	r3, r2
	
	div	r4, r3, r6
	mul	r5, r4, r6
	sub	r5, r3, r5

pd_if:
	ble 	r4, r0, pd_end_if
pd_then:	
	addi	r2, r4, '0'
	call 	PrintChar
pd_end_if:
	addi	r2, r5, '0'
	call 	PrintChar

	ldw	ra, 20(sp)
	ldw	r6, 16(sp)
	ldw	r5, 12(sp)
	ldw	r4, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi	sp, sp, 24

	ret
	
	
#-------------------------------------------------------------

GetChar:
	subi	sp, sp, ?
	stw 	r4, ?(sp)
	stw	r3, ?(sp)
	# r2 not saved/restored because it is a return register

	
	

	
	