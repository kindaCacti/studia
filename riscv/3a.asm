.data
    input: .space 80
    prompt: .asciz "\ninput string >"
    answ: .asciz "\noutput string >"
   
.text
    li a7, 4
    la a0, prompt
    ecall
    
    li a7, 8
    la a0, input
    li a1, 80
    ecall
    
    la t0, input
text_loop:
    addi t1, t0, 0
    li t2, 0 # counter
count_loop:
    lb t3, (t1)
    li t6, 32 # 32 is a space
    beq t3, t6, count_loop_end
    li t6, 10 # 10 is \n
    beq t3, t6, count_loop_end
    beqz t3, count_loop_end
    li t6, 90
    li t5, 65
if:
    bgt t3, t6, end_if
    blt t3, t5, end_if
    addi t2, t2, 1
mod_if:
    li t6, 11
    bne t2, t6, mod_if_end
    addi t2, t2, -10
mod_if_end:
end_if:
    addi t1, t1, 1
    lb t3, (t1)
    li t6, 32 # 32 is a space
    beq t3, t6, count_loop_end
    li t6, 10 # 10 is \n
    beq t3, t6, count_loop_end
    beqz t3, count_loop_end
    b count_loop
count_loop_end:
    addi t2, t2, 48
replace_loop:
    li t6, 32
    lb t3, (t0)
    beqz t3, replace_loop_end
    beq t3, t6, replace_loop_end
    li t6, 10 # 10 is \n
    beq t3, t6, replace_loop_end
    sb t2, (t0)
    addi t0, t0, 1
    b replace_loop
replace_loop_end:
    lb t3, (t0)
    beqz t3, text_loop_end
    li t6, 10 # 10 is \n
    beq t3, t6, text_loop_end
    addi t0, t0, 1
    lb t3, (t0)
    beqz t3, text_loop_end
    li t6, 10 # 10 is \n
    beq t3, t6, text_loop_end
    b text_loop
text_loop_end:
    
    li a7, 4
    la a0, answ
    ecall
    li a7, 4
    la a0, input
    ecall