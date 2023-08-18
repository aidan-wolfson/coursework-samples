	.text
	.global _start
	.org	0x0000

_start:

/*
main::
	PrintString("ELEC 274 Lab 4\n\n")
	PrintString("Enter string 1:")
	GetString(str1)
	PrintChar(\n)
	PrintString("Enter string 2:")
	GetString(str2)
	PrintChar(\n)
	PrintInterleaved(str1, str2)
	PrintChar(\n)
*/

main:
	movia	sp, 0x007FFFFC

	movia 	r2, FIRST
	call	PrintString	# printing first string

	movia	r2, ENTER1
	call 	PrintString	# printing enter 1 string

	movia	r2, STR1
	call	GetString	# getting user inputted string

	movi	r2, '\n'
	call	PrintChar	# printing newline character

	movia	r2, ENTER2
	call 	PrintString

	movia	r2, STR2
	call	GetString	# getting second user inputted string

	movi	r2, '\n'
	call	PrintChar

	movia	r2, STR1
	movia 	r3, STR2
	call	PrintInterleaved	# calling PrintInterleaved
	
	movi	r2, '\n'
	call 	PrintChar
	
	break		

	

#---------------------------------------------------------
/*
PrintInterleaved(str1,str2)::
loop
	ch1 = GetChar(str1)
	if (ch1 is not 0) then
		PrintChar(ch)
		str1 = str1 + 1
	end if
	ch2 = GetChar(str2)
	if (ch2 is not 0) then
		PrintChar(ch)
		str2 = str2 + 1
	end if	
	if (ch1 and ch2 are 0) then
		exit loop
	end if
end loop 	branch to start if both strings have not returned 0 
*/

PrintInterleaved:
	subi 	sp, sp, 24
	stw	ra, 20(sp)
	stw	r6, 16(sp) 	# ch2
	stw	r5, 12(sp)	# ch1
	stw	r4, 8(sp) 	# str2
	stw 	r3, 4(sp)	# passed str2 -> str1
	stw 	r2, 0(sp) 	# passed str1

	mov 	r4, r3		# str2 in r4
	mov 	r3, r2		# str1 in r3

pi_loop:
	call 	GetChar
	mov 	r5, r2 			# placing ch1 into r5

	beq	r0, r5, pi_end_if	# if ch1 = 0, branch 
	call 	PrintChar		# printing ch1
	addi	r3, r3, 1		# incrementing str1 	

pi_end_if:
	call 	GetChar
	mov	r6, r2			# placing ch2 into r6
	
	beq 	r0, r6, pi_end_if2	# if ch2 = 0, branch
	call 	PrintChar		# printing ch2
	addi	r4, r4, 1 		# incrementing str2

pi_end_if2:
	bne	r0, r5, pi_loop
	bne 	r0, r6, pi_loop		# if either ch1 or ch2 are not 0, loop again

pi_end_loop:

	ldw	ra, 20(sp)
	ldw	r6, 16(sp)
	ldw	r5, 12(sp) 
	ldw	r4, 8(sp)
	ldw 	r3, 4(sp) 
	ldw 	r2, 0(sp) 
	addi	sp, sp, 24

	ret

#---------------------------------------------------------

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

#---------------------------------------------------------

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

#---------------------------------------------------------

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

#---------------------------------------------------------
/*
GetString(buf_ptr)::
  loop
    ch = GetChar()
    if (ch is the newline character '\n')
      exit loop
    end if
    PrintChar(ch)
    write ch to location given by buf_ptr
    buf_ptr = buf_ptr + 1
  end loop
  write 0 to location given by buf_ptr  -important!-
*/
#---------------------------------------------------------

GetString:
	subi	sp, sp, 20
	stw 	ra, 16(sp)
	stw 	r5, 12(sp)	# '\n'
	stw 	r4, 8(sp)	# ch
	stw	r3, 4(sp)	# buf_ptr
	stw	r2, 0(sp)	# passed buffer pointer address

	mov	r3, r2		# moving passed buf_ptr into r3
	movi 	r5, '\n'	# placing newline character into r5
gs_loop:
	call 	GetChar
	mov 	r4, r2		# moving returned value from GetChar into r4
	
	beq	r4, r5, gs_end_loop

#if ch is \n, branch to gs_end_loop ---> if not, do not branch
gs_else:	
	mov	r2, r4		# preparing to pass ch into PrintChar
	call 	PrintChar
	
	stw	r4, 0(r3)	# writing ch to location given by buf_ptr	
	addi	r3, r3, 1	# incrementing buf_ptr
	br	gs_loop	

gs_end_loop:
	stw	r0, 0(r3)	# writing 0 to location given by buf_ptr

	ldw	ra, 16(sp)
	ldw	r5, 12(sp)
	ldw	r4, 8(sp)
	ldw	r3, 4(sp)
	ldw	r2, 0(sp)
	addi 	sp, sp, 20 
	
	ret



#---------------------------------------------------------

	.org	0x1000
STR1:	.skip 	100
STR2:	.skip	100
FIRST:	.asciz	"ELEC 274 Lab 4\n\n"
ENTER1:	.asciz	"Enter string 1: "
ENTER2:	.asciz	"Enter string 2: "

	.end


	


