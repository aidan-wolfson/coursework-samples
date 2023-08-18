	.text 
	.global _start
	.org	0x0000

_start:
main:
	movia	sp, 0x007FFFFC 	

	movia	r2, TITLE
	call	PrintString

	movia	r2, STR1
	call	PrintCentered

	movia 	r2, STR2
	call 	PrintCentered

	movi	r2, '\n'
	call	PrintChar

	break



#-------------------------------------------


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

#-------------------------------------------

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
	subi 	sp, sp, 16
	stw	ra, 12(sp)
	stw	r4, 8(sp) #ch
	stw	r3, 4(sp) #str_ptr
	stw	r2, 0(sp) #str_ptr -> len

	mov	r3, r2 
	movi	r2, 0
	
l_loop:
	#ch = read_byte_from address given by str
	ldb 	r4, 0(r3)

l_if:
	beq 	r4, r0, ps_end_loop	#exit loop if true

l_end_if:
	# str_ptr = str_ptr + 1
	addi 	r3, r3, 1 # str_ptr+1
	addi	r2, r2, 1 # len+1
	br	ps_loop

l_end_loop:
	ldw	ra, 12(sp)
	ldw 	r4, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi 	sp, sp, 16
	
	ret

#-------------------------------------------------------------

PrintDashes:
	subi 	sp, sp, 16
	stw	ra, 12(sp)
	stw	r4, 8(sp) #n-1
	stw	r3, 4(sp) #loop counter i
	stw 	r2, 0(sp) #passed value n & argument pass for printChar

	movi 	r3, 0
	mov 	r4, r2
	subi 	r4, r4, 1 #n-1
	movi 	r2, '-'

pd_for:
	bgt	r3, r4, pd_end_for
	call	PrintChar
	addi 	r3, r3, 1
	br	pd_for
	
pd_end_for:
	ldw 	ra, 12(sp)
	ldw	r4, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi	sp, sp, 16

	ret

#-------------------------------------------------------------

PrintCentered:
	subi 	sp, sp, 28
	stw	ra, 24(sp)
	stw 	r7, 20(sp) #immediate values for arithmetic
	stw	r6, 16(sp) #arithmetic stuff
	stw 	r5, 12(sp) #str_ptr
	stw	r4, 8(sp) #n
	stw	r3, 4(sp) #len
	stw	r2, 0(sp)

	mov	r5, r2
	call 	Length
	mov 	r3, r2 		#length->len register
	mov 	r6, r3  	#copying len to r6
	div 	r6, r6, r7
	movi 	r7, 20
	sub 	r6, r7, r6 	#final value for n
	mov 	r4, r6

	mov	r2, r4 		#preparing to call PrintDashes
	call 	PrintDashes

	mov	r2, r5 		#preparing to call PrintString
	call 	PrintString

pc_if:
	add	r6, r4, r4
	add 	r6, r6, r3
	movi	r7, 40
	ble	r6, r7, pc_end_if
	
pc_then:
	subi	r4, r4, 1

pc_end_if:
	mov 	r2, r4
	call	PrintDashes

	movi	r2, '\n'
	call 	PrintChar

	ldw	ra, 24(sp)
	ldw 	r7, 20(sp) 
	ldw	r6, 16(sp) 
	ldw 	r5, 12(sp) 
	ldw	r4, 8(sp) 
	ldw	r3, 4(sp) 
	ldw	r2, 0(sp)
	addi	sp, sp, 28

	ret

#-------------------------------------------------------------


	.org 	0x1000
TITLE:	.asciz	"\nELEC 274 Lab 2\n\n"
STR1:	.asciz	"this is"
STR2:	.asciz	"a test"
	.end





