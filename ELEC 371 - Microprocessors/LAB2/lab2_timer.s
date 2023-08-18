#-----------------------------------------------------------------------------
# This template source file for ELEC 371 Lab 2 experimentation with interrupts
# also serves as the template for all assembly-language-level coding for
# Nios II interrupt-based programs in this course. DO NOT USE the approach
# shown in the vendor documentation for the DE0 Basic (or Media) Computer.
# The approach illustrated in this template file is far simpler for learning.
#
# Dr. N. Manjikian, Dept. of Elec. and Comp. Eng., Queen's University
#-----------------------------------------------------------------------------

	.text		# start a code segment 

	.global	_start	# export _start symbol for linker 

#-----------------------------------------------------------------------------
# Define symbols for memory-mapped I/O register addresses and use them in code
#-----------------------------------------------------------------------------

# the symbols below are for the Lab 2 timer experiment

	.equ	TIMER_STATUS, 0x10002000
	.equ	TIMER_CONTROL, 0x10002004
	.equ	TIMER_START_LO, 0x10002008
	.equ	TIMER_START_HI, 0x1000200C
	
	.equ	LEDS, 0x10000010
	.equ 	BUTTON1, 0x10000050
	.equ 	SWITCHES, 0x10000040
	.equ	SEVENSEG, 0x10000020
	
#-----------------------------------------------------------------------------
# Define two branch instructions in specific locations at the start of memory
#-----------------------------------------------------------------------------

	.org	0x0000	# this is the _reset_ address 
_start:
	br	main	# branch to actual start of main() routine 

	.org	0x0020	# this is the _exception/interrupt_ address
 
	br	isr	# branch to start of interrupt service routine 
			# (rather than placing all of the service code here) 

#-----------------------------------------------------------------------------
# The actual program code (incl. service routine) can be placed immediately
# after the second branch above, or another .org directive could be used
# to place the program code at a desired address (e.g., 0x0080). It does not
# matter because the _start symbol defines where execution begins, and the
# branch at that location simply forces execution to continue where desired.
#-----------------------------------------------------------------------------

main:
	movia	sp, 0x007FFFC		# initialize stack pointer

	call	Init			# call hw/sw initialization subroutine

	stw 	r0, COUNT(r0)		# perform any local initialization before main loop 

main_loop:
			# body of main loop (reflecting typical embedded
			#   software organization where execution does not
			#   terminate)
	ldw	r2, COUNT(r0)
	addi	r2, r2, 1
	stw	r2, COUNT(r0)

	call	Switches
	# r2 contains x
	call 	SevenSeg
	
	br main_loop

#-----------------------------------------------------------------------------
# This subroutine should encompass preparation of I/O registers as well as
# special processor registers for recognition and processing of interrupt
# requests. Preparation of program data variables can also be included here.
#-----------------------------------------------------------------------------

Init:				# make it modular -- save/restore registers
	subi	sp, sp, 16
	stw		ra, 12(sp)
	stw		r4, 8(sp)
	stw		r3, 4(sp)	
	stw 	r2, 0(sp) 	

# body of Init() subroutine
	# stwio to write two 16-bit patterns to TIMER_HI and TIMER_LO registers (for initial/start count value)
	# split 32-bit value "for desired duration" into two 16-bit pieces
	# use movia to place 16 bit value in a register
	# then, write to timer control register, TIMER_CONTROL, the appropriate bit battern to enable continuous mode with interrupts
	# startup of the timer (TIMER_STATUS?)

	# preparing period (1s) by setting starting count value
	# for period 1s, starting value of count is 0x2FAF080
	
	movia	r3, TIMER_START_HI
	movia	r4, TIMER_START_LO

	movia	r2, 0x02FA
	stwio	r2, 0(r3)

	movia	r2, 0xF080
	stwio	r2, 0(r4)

	# writing bit pattern to control register
	
	movia	r3, TIMER_CONTROL
	movi	r2, 0b0111
	stwio	r2, 0(r3)
	# wrctl	TIMER_CONTROL, r2
	
	movi	r2, 1 
	wrctl 	ienable, r2
	wrctl 	status, r2
	
	ldw	ra, 12(sp)
	ldw	r4, 8(sp)
	ldw 	r3, 4(sp)	
	ldw 	r2, 0(sp)
	addi 	sp, sp, 16
	
		# body of Init() subroutine

	ret

#-----------------------------------------------------------------------------
# The code for the interrupt service routine is below. Note that the branch
# instruction at 0x0020 is executed first upon recognition of interrupts,
# and that branch brings the flow of execution to the code below. Therefore,
# the actual code for this routine can be anywhere in memory for convenience.
# This template involves only hardware-generated interrupts. Therefore, the
# return-address adjustment on the ea register is performed unconditionally.
# Programs with software-generated interrupts must check for hardware sources
# to conditionally adjust the ea register (no adjustment for s/w interrupts).
#-----------------------------------------------------------------------------

isr:
	subi	sp, sp, 12	#  save register values, except ea which
	stw	ra, 8(sp)
	stw	r3, 4(sp)	#  must be modified for hardware interrupts
	stw	r2, 0(sp)	

	subi	ea, ea, 4	# ea adjustment required for h/w interrupts

				# body of interrupt service routine
				#   (use the proper approach for checking
				#    the different interrupt sources)
	
	# check timer interface as possible interrupt source
	# as if there are multiple sources
	# get ipending contents and place in register
	# perform AND operation placing the result in a different reg to isolate bit for an interface
	
	rdctl 	r2, ipending
	beq 	r2, r0, exit_isr
		
check_timer:
	# rdctl 	r2, TIMER_STATUS
	# movia	r2, TIMER_CONTROL
	# ldwio	r2, 0(r2)
    	andi	r3, r2, 1
		beq 	r3, r0, exit_isr	# if bit is a 1, respond to the interrupt	
    	movia 	r2, TIMER_STATUS	
    	stwio 	r0, 0(r2)
    	movia 	r2, LEDS
    	ldwio 	r3, 0(r2)
    	xori 	r3, r3, 1
    	stwio 	r3, 0(r2)
	

exit_isr:
	# if bit is not a 1, branch to this 
	

	ldw	ra, 8(sp)
	ldw	r3, 4(sp)	# restore register values
	ldw	r2, 0(sp)	
	addi	sp, sp, 12	
	
	# check that you have the Cont. bit set when you initialise
	# reset the status bit

	eret			# interrupt service routines end _differently_
				# than subroutines; execution must return to
				# to point in main program where interrupt
				# request invoked service routine
	
Switches:
	# r2 returns DE0 switch settings
	# loop until BUTTON1 has been pressed
	
	# check bit 1 of button1 data register
	
	subi	sp, sp, 8
	stw		r4, 4(sp)
	stw		r3, 0(sp)
	


s_loop:
	movia 	r3, BUTTON1
	ldwio	r3, 0(r3)
	andi 	r4, r3, 0x2
	beq		r4, r0, s_loop
	movia 	r2,	SWITCHES
	ldwio	r2, 0(r2)
	

	ldw		r4, 4(sp)
	ldw		r3, 0(sp)
	addi	sp, sp, 8
	
	
	ret
	
	
#------------------------------------

SevenSeg:
	
		subi	sp, sp, 8
		stw		r4, 4(sp)
		stw		r3, 0(sp)
		# r2 has passed de0 switch settings 
		
		beq		r2, r0, ss_zero
		br		ss_nonzero
		
ss_zero:
		movia	r3, SEVENSEG
		movi	r4, 0b00111111 	# setting the seven bits to display 0
		stwio	r4, 0(r3)
		
		br	ss_exit

ss_nonzero:
		movia	r3, SEVENSEG
		movi	r4, 0b01010100	# setting the seven bits to display 'n'
		stwio	r4, 0(r3)
		
ss_exit:
		
		
		ldw		r4, 4(sp)
		ldw		r3, 0(sp)	
		addi	sp, sp, 8
		
		ret
#-----------------------------------------------------------------------------
# Definitions for program data, incl. anything shared between main/isr code
#-----------------------------------------------------------------------------

	.org	0x1000		# start should be fine for most small programs


COUNT:	.skip	4		# define/reserve storage for program data

	.end
