.data
    input: .space 80
    prompt: .asciz "\ninput string >"
    msg: .asciz "\noutput string >"
    
.text
.globl main

b main

# a0 - begin pointer, a1 - end pointer, a2 - replacing char
replace_function:
    mv t0, a0
    mv t1, a1
    mv t2, a2
replace_loop:
    sb t2, (t0)
    beq t0, t1, replace_loop_end
    addi t0, t0, 1
    b replace_loop
replace_loop_end:    
    ret

#a0 - starting position, a1 - what to find
find_pos:
    mv t0, a0
finding_loop:
    lb t6, (t0)
    beq t6, a1, finding_loop_end
    li t5, 10
    beq t6, t5, bad_ending
    addi t0, t0, 1
    b finding_loop
finding_loop_end:
    mv a0, t0
    ret
bad_ending:
    li a0, 0
    ret

# where to start the program
main:
    li a7, 4
    la a0, prompt
    ecall
    
    li a7, 8
    la a0, input
    li a1, 80
    ecall
    
# get the markers
    la t0, input
    lb s0, (t0)
    addi t0, t0, 1
    lb s1, (t0)

# replace first three chars with space
    la a0, input
    addi a1, a0, 2
    li a2, 32
    jal replace_function

# find begin pointer
    la t0, input
    addi t0, t0, 3
    mv t1, t0
    mv a0, t1
    mv a1, s0
    jal find_pos
    beqz a0, do_not_replace
    mv s2, a0
    
# find end pointer
    mv a0, s2
    mv a1, s1
    jal find_pos
    beqz a0, do_not_replace
    mv s3, a0
    
# replace string between start and end pointer with *
    mv a0, s2
    mv a1, s3
    li a2, 42
    jal replace_function

do_not_replace:
    li a7, 4
    la a0, msg
    ecall
    li a7, 4
    la a0, input
    ecall
