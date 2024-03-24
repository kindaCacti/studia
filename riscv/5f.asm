.data
    input: .space 80
    prompt: .asciz "\ninput text >"
    msg: .asciz "\noutput text >"

.text
# skip all functions at the beginning
b main

# a0 - string pointer, a1 - char to find
find_char:
    mv t0, a0
find_loop:
    lb t1, (t0)
    beq t1, a1, find_loop_end
    beqz t1, find_bad_ending
    addi t0, t0, 1
    b find_loop
find_loop_end:
    mv a0, t0
    ret
find_bad_ending:
    li a0, 0
    ret


# a0 - string pointer
replace_function:
    mv s0, a0
    
# find first [
    mv a0, s0
    li a1, 91
    mv s7, ra
    jal find_char
    mv ra, s7
    mv s1, a0

# find first ]
    mv a0, s1
    li a1, 93
    mv s7, ra
    jal find_char
    mv ra, s7
    mv s2, a0

# move everything to the left by begin_pointer
    la t0, input
    mv t1, s1
move_loop:
    lb t2, (t1)
    sb t2, (t0)
    beq t1, s2, move_loop_end
    addi t0, t0, 1
    addi t1, t1, 1
    b move_loop
move_loop_end:
    sub t0, s2, s1
    sub s2, s2, t0
    addi s2, s2, 1
    sub s1, s1, t0
    addi s1, s1, 1
    
# set null to end pointer value
    addi t0, s2, 1
    li t1, 0
    sb t1, (t0)

# return ptr_end - ptr_begin - 1
    sub t0, s2, s1
    addi t0, t0, -1
    mv a0, t0
    ret

main:
    li a7, 4
    la a0, prompt
    ecall
    li a7, 8
    la a0, input
    li a1, 80
    ecall
    
    la a0, input
    jal replace_function
    mv t0, a0
    
    li a7, 4
    la a0, msg
    ecall
    li a7, 4
    la a0, input
    ecall
    li a7, 1
    mv a0, t0
    ecall