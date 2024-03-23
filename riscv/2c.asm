.data
    input: .space 80
    prompt: .asciz "input text: >"
    msg1: .asciz "output text: >"
   
.text
    li a7, 4
    la a0, prompt
    ecall
    
    li a7, 8
    la a0, input
    li a1, 80
    ecall
    
    la t0, input # it0 = *str
    la t1, input # it1 = *str
text_loop:
    addi t3, t1, 0 # it3 = it1 (remembering this address)
    beq t1, t0, swap_loop_end
    addi t2, t1, -1 # it2 = it1 + 1
swap_loop:
    lb t4, (t1)
    lb t5, (t2)
    li t6, 10
    beq t4, t6, swap_loop_end # if *it1 == '\n' break;
    beq t5, t6, swap_loop_end # if *it2 == '\n' break;
    lb t6, (t0)
    beq t4, t6, swap_loop_end # if *it1 == *it0 break;
    sb t4, (t2)
    sb t5, (t1)
    addi t1, t1, -1 # it1--;
    addi t2, t2, -1 # it2--;
    b swap_loop
swap_loop_end:
    addi t1, t3, 0 # t1 = t3
    addi t1, t1, 2 # t1 = t1 + 2
    addi t0, t0, 1 # it0 = t0 + 1
    lb t6, (t1) # t6 = *t1
    li t5, 10 # t5 = (char)10
    beq t6, t5, text_loop_end
    bgtz t6, text_loop
text_loop_end:
    
    

    li a7, 4
    la a0, msg1
    ecall
    li a7, 4
    la a0, input
    ecall