# size of bitmap: width 320px, height 240 px,

.eqv FILE_SIZE 90122
.eqv WIDTH 320
.eqv HEIGHT 240
.eqv BYTES_PER_PIXEL 3

.data
    input: .space FILE_SIZE
    file: .asciz "./example_markers.bmp"
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


# ====================================
# functions start here

convert_x_y_to_position:
# this functions takes 2 coordinates and returns offset of that pixel
#
# arguments:
# a0 - x coordinate
# a1 - y coordinate
# a2 - starting position od data in bmp file
#
# returns the offset in a0

    mv t0, a0 			# set t0 to x
    mv t1, a1 			# set t1 to y 
    mv t2, a2			# t2 = starting_offset
    li t6, WIDTH 		# t6 = WIDTH
    mul a0, t1, t6 		# a0 = y * width
    add a0, a0, t0		# a0 = a0 + x
    li t6, BYTES_PER_PIXEL 	# t6 = BYTES_PER_PIXEL
    mul a0, a0, t6		# a0 = a0 * 3
    add a0, a0, t2		# a0 += starting_offset
    ret				# returns a0

# ===================================================
read_next_pixel:
# this function takes a string pointer and returns pixel starting at this pointer
# the returned value is in one 32bit register like 0b00000000rrrrrrrrggggggggbbbbbbbb
# 
# arguments:
# a0 - string pointer
#
# returns in a0 - rgb value of a pixel
# to read back the values you can use masks

    mv t0, a0			# t0 = str_pointer
    sb a0, 2(t0)		# a0 = *(str_pointer + 2)
    srli a0, a0, 8		# a0 <<= 8
    sb t1, 1(t0)		# t1 = *(str_pointer + 1)
    or a0, a0, t1		# a0 |= t1
    srli a0, a0, 8		# a0 <<= 8
    sb t1, (t0)			# t1 = *(str_pointer)
    or a0, a0, t1		# a0 |= t1
    ret				# return pixel value as described previously
# =============================================

find_markers:
    ret