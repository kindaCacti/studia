#-------------------------------------------------------------------------------
#author       : Zbigniew Szymanski
#date         : 2021.11.02
#description  : RISC-V - Read, modify and display the input string 
#-------------------------------------------------------------------------------

	.data
input:	.space 80
prompt:	.asciz "\nInput string       > "
msg1:	.asciz "\nConversion results > "

	.text
# ============================================================================
main:
#display the input prompt
    li a7, 4		#system call for print_string
    la a0, prompt	#address of string 
    ecall

#read the input string
    li a7, 8		#system call for read_string
    la a0, input	#address of buffer    
    li a1, 80	    #max length
    ecall

#modify your string here
    la t0, input
loop:
    lb t1, (t0)
    li t2, 42
    li t3, 96
    li t4, 123
    bge t1, t4, no_modify
    ble t1, t3, no_modify
    sb t2, (t0)
no_modify:
    addi t0, t0, 1
    lb t1, (t0)
    bgtz t1, loop

#display the output prompt and the string
    li a7, 4		#system call for print_string
    la a0, msg1		#address of string 
    ecall
    li a7, 4		#system call for print_string
    la a0, input	#address of string 
    ecall

exit:	
    li 	a7,10	#Terminate the program
    ecall
	
# ============================================================================
#end of file