    .data
input: .space 80
prompt: .asciz "\npodaj tekst >"
msg1: .asciz "\ntekst po konwersji >"

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
    lb t1, (t0)
    li t2, 64
    li t3, 91
    ble t1, t2, no_modify
    bge t1, t3, no_modify
    li t4, 42
    sb t4, (t0)
no_modify:
    addi t0, t0, 1
    lb t1, (t0)
    bgtz t1, loop
    
    li a7, 4
    la a0, prompt
    ecall
    li a7, 4
    la a0, input
    ecall