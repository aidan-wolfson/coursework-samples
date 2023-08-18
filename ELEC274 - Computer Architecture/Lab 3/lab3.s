	.text
	.global _start
	.org	0x0000

_start:

/*
main::
	PrintString("Enter a decimal value between 00 and 99:\n")
	num = GetDec99()
	PrintString("Entered valye divided by two is:")
	half = num / 2
	PrintDec99(half)
	PrintChar(\n)
*/

main:
	movia 	sp, 0x007FFFFC

	movia 	r2, FIRST
	call 	PrintString	# printing first string
	
	call 	GetDec99
	mov	r3, r2		# moving returned value into r3 (num)
	
	movia	r2, SECOND
	call 	PrintString	# printing second string
	
	movi	r2, 2
	div	r2, r3, r2	# num/2
	stw	r2, HALF(r0)	# store the value in memory - global variable HALF

	ldw	r2, HALF(r0)
	call 	PrintDec99	# calling PrintDec99() for half

	movi	r2, '\n'	
	call 	PrintChar

	break
#------------------------------------------------------------

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

#------------------------------------------------------------

GetChar:
	subi	sp, sp, 12
	stw	r5, 8(sp) #st
	stw 	r4, 4(sp) #data
	stw	r3, 0(sp) 
	#r2 not saved/restored because it is a return register

	movia	r3, 0x10001000 	#point to first memory-mapped I/O register (JTAG UART data register)
gc_loop:
	ldwio	r4, 0(r3)	#read bits from data register into r4
	andhi	r4, r4, 0x8000	
	beq	r4, r0, gc_loop	#if bits are zero, loop again

gc_end_loop:
	andhi 	r2, r4, 0xFF

	ldw	r5, 8(sp)
	ldw	r4, 4(sp)
	ldw	r3, 0(sp)
	addi	sp, sp, 12

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


#------------------------------------------------------------
/*
GetDec99::
	ch = GetChar()
	PrintChar(ch)
	val = ch - '0'
	val = val * 10
	ch = GetChar()
	PrintChar(ch)
	val = val + (ch - '0')
	PrintChar(\n)
	return (val)
*/

GetDec99:
	subi	sp, sp, 16
	stw	ra, 12(sp)
	stw 	r5, 8(sp) # constant 10
	stw 	r4, 4(sp) # val
	stw 	r3, 0(sp) # ch
	# not saving/restoring r2 because it passes val back to calling code

	movi	r5, 10
gd_main:
	call 	GetChar		# returns ch 
	mov 	r3, r2		# copying returned value to ch
	call 	PrintChar	# calling PrintChar(ch)
	
	subi	r4, r3, '0'	
	mul	r4, r4, r5

	call 	GetChar
	mov 	r3, r2
	call 	PrintChar

	subi 	r3, r3, '0'
	add	r4, r4, r3	
	
	movi 	r2, '\n'	
	call	PrintChar	# printing new line character	

	mov	r2, r4		# preparing r2 to return val

	ldw	ra, 12(sp)
	ldw 	r5, 8(sp) # constant 10
	ldw 	r4, 4(sp) # val
	ldw 	r3, 0(sp) # ch
	addi	sp, sp, 16

	ret


#------------------------------------------------------------

	.org	0x1000
HALF:	.skip	4 
FIRST:	.asciz	"Enter a decimal value between 00 and 99:\n"
SECOND:	.asciz	"Entered value divided by two is: "
	.end

