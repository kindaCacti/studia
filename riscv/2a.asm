.data
    input: .space 80
    prompt: .asciz "input your text: >"
    msg1: .asciz "string after conversion is: >"

.text
    li a7, 4
    la a0, prompt
    ecall
    
    li a7, 8
    la a0, input
    li a1, 80
    ecall
    
    la t0, input
loop:
    addi t1, t0, 1
    lb t6, (t1)
    li t4, 10
    beq t6, t4, exit
    beqz t6, exit
    lb t5, (t0)
    sb t6, (t0)
    sb t5, (t1)
    
    addi t0, t0, 2
    lb t5, (t0)
    bgtz t5, loop
exit:
    
    li a7, 4
    la a0, msg1
    ecall
    li a7, 4
    la a0, input
    ecall