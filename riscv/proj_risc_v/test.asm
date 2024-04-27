# this code works for a test file which is 4x3

.eqv FILE_SIZE 230500
.eqv HEIGHT 240
.eqv WIDTH 320
.eqv BYTES_PER_PIXEL 3
.eqv MARKER_COLOR 0

.data
    input: .space FILE_SIZE
    d_new_line: .asciz "\n\n"
    file_path: .asciz "uwalacz1.bmp"
    start_msg: .asciz "\nthe program started running...\n"
    end_msg: .asciz "\nthe program ended running.\n"
    error_msg: .asciz "\nerror occurred\n"
    
.text
# writing the start message
    li a7, 4
    la a0, start_msg
    ecall

# opening a file
    li a7, 1024
    la a0, file_path
    li a1, 0
    ecall
    
# if file was correctly opened go to correct
    li t0, -1
    bne a0, t0, correct
    
# write error message
    li a7, 4
    la a0, error_msg
    ecall
    b end
correct:
# save the file descriptor to s0
    mv s0, a0

# read from file
    li a7, 63
    mv a0, s0
    la a1, input
    li a2, FILE_SIZE
    ecall

# get starting pointer
    la a0, input
    jal read_starting_position

# save starting position to s1
    mv s1, a0

# getting things from a file works
    mv a1, a0
    li a0, 0
    li a1, 0
    mv a2, s1
    jal get_xy_pixel
    mv t0, a0

# print given pixel
    li a7, 1
    ecall
    li a7, 4
    la a0, d_new_line
    ecall
        
end:
# close the file
    li a7, 57
    mv a0, s0
    ecall
    
# check line height for pixel (1,14)
    li a0, 1
    li a1, 14
    mv a2, s1
    jal line_height
    li a7, 1
    ecall
    li a7, 4
    la a0, d_new_line
    ecall
    
# check line height for pixel (10,31)
    li a0, 10
    li a1, 31
    mv a2, s1
    jal line_height
    li a1, 0
    li a7, 1
    ecall
    li a7, 4
    la a0, d_new_line
    ecall

# write end of running message
    li a7, 4
    la a0, end_msg
    ecall

# end the program
    li a7, 10
    ecall
    
    
#=======================================
# functions start here
read_starting_position:
# a0 - file contents pointer
# returns a0 - starting pointer
    lb t1, 10(a0)
    add a0, a0, t1
    ret

get_xy_pixel:
# a0 - x_coordinate
# a1 - y_coordinate
# a2 - starting_pointer
# returns a0 - the pixel as 00000000rrrrrrrrggggggggbbbbbbbb
    li t0, BYTES_PER_PIXEL
    li t1, WIDTH
    li t2, HEIGHT
    sub a1, t2, a1 	# reverse the height
    addi a1, a1, -1 	# reverse the height
    mul t2, a1, t1	# t2 = y_coordinate * width
    add t2, t2, a0	# t2 += x_coordinate
    mul t2, t2, t0	# t2 *= bytes_per_pixel
    add t2, t2, a2      # t2 = starting_pointer + byte_offset(t2)
    li a0, 0        	# out = 0
    lb t1, 2(t2)	# tmp = red_value
    or a0, a0, t1   	# out |= red_value
    slli a0, a0, 8	# out <<= 8
    lb t1, 1(t2)	# tmp = green_value
    or a0, a0, t1	# out |= green_value
    slli a0, a0, 8	# out <<= 8
    lb t1, (t2)		# tmp = blue_value
    or a0, a0, t1	# out |= blue_value
    ret
#=================================================================

line_height:
# a0 - starting_x
# a1 - starting_y
# a2 - data_starting_pointer
# returns a0 - height of a line starting at that point
    mv t0, a0   # t0 is now current_x
    mv t1, a1   # t1 is now current_y
    li t2, 0    # t2 is now current_pixel
    li t3, 0    # t3 is now current_height
    mv t5, a2	# t5 is now starting_pointer
    
    line_height_loop:
        li t4, HEIGHT       # load t4 with height
        bge t1, t4, line_height_loop_end    # if current_y >= height then break the loop
        
        sw ra, (sp)         # save return address
        sw t0, 4(sp)        # save current_x 
        sw t1, 8(sp)        # save current_y 
        sw t3, 12(sp)       # save current_height
        sw t5, 16(sp)       # save starting_pointer
        addi sp, sp, 20     # add 16 to stack pointer
        mv a0, t0           # move current_x to a0
        mv a1, t1           # move current_y to a1
        mv a2, t5
        jal get_xy_pixel    # get_xy_pixel(current_X, current_y)
        addi sp, sp, -20    # add -16 to stack pointer
        lw ra, (sp)         # load return address from stack
        lw t0, 4(sp)        # load current_x from stack
        lw t1, 8(sp)        # load current_y from stack
        lw t3, 12(sp)       # load current_height from stack
        lw t5, 16(sp)       # load starting_pointer from stack
        
        mv t2, a0           # move return of the function to current_pixel
        li t4, MARKER_COLOR # load t4 with marker_color
        bne t2, t4, line_height_loop_end # if current_pixel is equal to marker_color then break the loop
        addi t3, t3, 1      # current_height++;
        addi t1, t1, 1      # current_y++;
        b line_height_loop
    line_height_loop_end:
    mv a0, t3   # return current_height
    ret
#==============================================================

does_line_not_have_color:
# a0 - starting_x
# a1 - starting_y
# a2 - ending_y (including this y)
# returns 1 if line does not have marker_color in it else returns 0
# dlnhc are the initials of the function
    mv t0, a0		    # save starting_x to t0
    mv t1, a1		    # current_y = starting_y (current_y = t1)
    mv t2, a2		    # save ending_y to t2
    li t3, 0		    # load t3 with 0, to use it in later conditions
    blt t0, t3, dlnhc_return_true # if outside of an image reutrn true
    blt t1, t3, dlnhc_return_true # if outside of an image return true
    
    dlnhc_line_loop:
        bgt t1, t2, dlnhc_return_true 	# if current_y == ending_y then return true
        				# TODO: current_pixel = get_xy_pixel(starting_x, current_y)
        mv t4, a0		    	# t4 = returned value (current_pixel)
        li t5, MARKER_COLOR	    	# t5 = marker_color for later conditions
        beq t4, t5, dlnhc_return_false 	# if current_pixel == marker_color then return false
        addi t1, t1, 1			# current_y++
    	b dlnhc_line_loop   		# basically a while(true) loop
    
    dlnhc_return_true:
    li a0, 1	    	    # return true
    ret
    dlnhc_return_false:
    li a0, 0		    # return false
    ret
#=======================================================

check_for_marker:
# a0 - starting_x
# a1 - starting_y
# returns 1 if there is a marker which upper-left corner is in this coordinates else returns 0
    mv t0, a0		    # save starting_x
    mv t1, a0		    # save starting_y
