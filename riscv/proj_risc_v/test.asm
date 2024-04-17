# size of bitmap: width 320px, height 240 px,

.eqv FILE_SIZE 90122

.data
    input: .space FILE_SIZE
    file: .asciz "C:/Users/cacti/Desktop/risc-v/source.bmp\0"
    msg1: .asciz "\n\nthe program is running...\n\n"
    msg2: .asciz "\n\nthe program has ended\n\n"
    error_message: .asciz "failed while opening a file\n\n"

.text
    li a7, 4
    la a0, msg1
    ecall
    
    #opening a file in read only mode
    li a7, 1024
    la a0, file
    li a1, 0
    ecall
        
    li a6, -1
    bne a0, a6, correct
    
    li a7, 4
    la a0, error_message
    ecall
    j end
    
correct:
    #save file descriptor in s0
    mv s0, a0
    
    #reading from the file
    li a7, 63
    mv a0, s0 #rewriting this just in case
    la a1, input
    li a2, 80
    ecall
    
    #print the contents of the file
    li a7, 4
    la a0, input
    ecall
    
    #close the file
    mv a0, s0
    li a7, 57
    ecall

end:
    #print end of program message
    li a7, 4
    la a0, msg2
    ecall
    
    li a7 10
    ecall



#functions start here
#a0 - string pointer
read_byte_by_byte:
    
