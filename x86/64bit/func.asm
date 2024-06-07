section .text
global read_pixel
global line_height
global does_line_not_have_marker
global is_marker
global check_is_marker

check_is_marker:
    push rbp
    mov rbp, rsp

    mov r8, rsi
    push 0 ; x coordinate [-8]
    push 0  ; y coordinate [-16]
    push 0  ; counter      [-24]


    mov rsi, rdx
    push rsi    ; [-32]

    xor rax, rax
    mov al, BYTE[rsi+23]
    shl rax, 8
    mov al, BYTE[rsi+22]
    push rax    ; height [-40]


    xor rax, rax
    mov al, BYTE[rsi+19]
    shl rax, 8
    mov al, BYTE[rsi+18]
    push rax    ; width [-48]

    xor rax, rax
    mov al, BYTE[rsi+10]
    push rax

    .loop_y:
        .loop_x:
            push QWORD[rbp-16]
            push QWORD[rbp-8]
            call is_marker
            add rsp, 16
            cmp rax, 0

            je .dont_add

            mov rax, QWORD[rbp-24]
            mov rcx, 4
            mul rcx
            add rax, rdi
            mov rsi, QWORD[rbp-8]
            mov DWORD[rax], esi

            mov rax, QWORD[rbp-24]
            mov rcx, 4
            mul rcx
            add rax, r8
            mov rsi, QWORD[rbp-16]
            mov DWORD[rax], esi

            inc QWORD[rbp-24]

            .dont_add:
            inc QWORD[rbp-8]
            mov rcx, QWORD[rbp-48]
            cmp QWORD[rbp-8], rcx
            jl .loop_x
        mov QWORD[rbp-8], 0
        inc QWORD[rbp-16]
        mov rcx, QWORD[rbp-40]
        cmp QWORD[rbp-16], rcx
        jl .loop_y

    mov rax, QWORD[rbp-24]
    ;mov rax, 100
    mov rsp, rbp
    pop rbp
    ret

read_pixel:
    push rbp
    mov rbp, rsp
    mov rcx, QWORD[rbp+16]        ; rcx = x_coordinate
    mov rsi, QWORD[rbp+48]       ; rsi = height
    mov rax, QWORD[rbp+24]       ; rax = y_coordinate
    sub rsi, rax            ; rsi -= rax
    sub rsi, 1              ; rsi -= 1 (we now reversed the y coordinate)
    mov rax, QWORD[rbp+40]       ; rax = width
    mul rsi                 ; rsi *= width
    mov rsi, rax
    add rcx, rsi            ; rcx += vectically_skipped_pixels
    mov rax, 3
    mul rcx                 ; byte_offset = pixel_id * 3 (3 bytes per pixel)
    mov rcx, rax
    xor rax, rax
    mov al, BYTE[rbp+32]    ; rax = data_start_offset
    add rcx, rax            ; byte_offset += data_start_offset
    mov rsi, QWORD[rbp+56]        ; rsi = data_pointer
    add rsi, rcx            ; data_pointer += byte_offset
    xor rax, rax            ; clear rax
    mov al, BYTE[rsi]       ; first 8 bits of rax = blue value

    shl rax, 8              ; shift left by 8 bits
    mov al, BYTE[rsi+1]     ; first 8 bits of rax = green value
    shl rax, 8              ; shift left by 8 bits
    mov al, BYTE[rsi+2]     ; first 8 bits of rax = red value
    mov rsp, rbp
    pop rbp
    ret

line_height:
    push rbp
    mov rbp, rsp
    xor rcx, rcx            ; rcx = 0 // line_height
    mov rsi, QWORD[rbp+24]       ; rsi = current_y
    .loop:
        mov rax, QWORD[rbp+48]
        cmp rsi, rax
        jge .loop_end
        push rcx
        push QWORD[rbp+56]
        push QWORD[rbp+48]
        push QWORD[rbp+40]
        push QWORD[rbp+32]
        push rsi
        push QWORD[rbp+16]
        call read_pixel
        pop rsi
        pop rsi
        add rsp, 32
        pop rcx
        cmp rax, 0
        jne .loop_end
        inc rsi
        inc rcx
        jmp .loop
    .loop_end:
    mov rax, rcx
    mov rsp, rbp
    pop rbp
    ret

does_line_not_have_marker:
    push rbp
    mov rbp, rsp
    mov rcx, QWORD[rbp+16]
    mov rax, QWORD[rbp+48]
    cmp rcx, rax
    jge .return_true
    mov rax, 0
    cmp rcx, rax
    jl .return_true
    mov rsi, QWORD[rbp+16]
    mov rax, 0
    cmp rsi, rax
    jl .return_true
    mov rcx, QWORD[rbp+24]
    .loop:
        mov rsi, QWORD[rbp+32]
        cmp rcx, rsi
        jg .return_true
        push QWORD[rbp+64]
        push QWORD[rbp+56]
        push QWORD[rbp+48]
        push QWORD[rbp+40]
        push rcx
        push QWORD[rbp+16]
        call read_pixel
        add rsp, 48
        cmp rax, 0
        je .return_false
        mov rcx, QWORD[rbp+24]
        inc rcx
        mov QWORD[rbp+24], rcx
        jmp .loop
.return_true:
    mov rax, 1
    mov rsp, rbp
    pop rbp
    ret
.return_false:
    mov rax, 0    
    mov rsp, rbp
    pop rbp
    ret

; extern int isMarker(int x, int y, int data_offset, int width, int height, unsigned char* data);
is_marker:
    push rbp
    mov rbp, rsp
    push QWORD[rbp+56]
    push QWORD[rbp+48]
    push QWORD[rbp+40]
    push QWORD[rbp+32]
    push QWORD[rbp+24]
    push QWORD[rbp+16]
    call read_pixel
    add rsp, 48
    cmp rax, 0
    jne .return_false
    add rsp, -48

    add rsp, 16
    mov rcx, QWORD[rbp+24]
    add rcx, -1
    push rcx
    push rcx
    push QWORD[rbp+16]
    call does_line_not_have_marker
    add rsp, 56
    cmp rax, 0
    je .return_false
    add rsp, -56

    add rsp, 24
    push QWORD[rbp+24]
    push QWORD[rbp+16]
    call line_height
    add rsp, 48
    push QWORD[rbp+16]   ; current_x [rbp-8]
    push rax            ; current_height [rbp-16]
    push rax            ; last_height [rbp-24]
    push rax            ; best_height [rbp-32]
    push 0              ; has_step [rbp-40]
    push -1             ; step_x [rbp-48]

    mov rcx, QWORD[rbp+16]
    add rcx, -1
    mov rsi, QWORD[rbp+24]
    add rsi, QWORD[rbp-16]
    dec rsi
    push QWORD[rbp+56]
    push QWORD[rbp+48]
    push QWORD[rbp+40]
    push QWORD[rbp+32]
    push rsi
    push QWORD[rbp+24]
    push rcx
    call does_line_not_have_marker
    add rsp, 104
    cmp rax, 0
    je .return_false
    add rsp, -104

    .loop:
        mov rcx, QWORD[rbp-8]
        inc rcx
        mov QWORD[rbp-8], rcx
        add rsp, 8
        cmp rcx, QWORD[rbp+40]
        jge .loop_end
        add rsp, 16

        push QWORD[rbp+24]
        push QWORD[rbp-8]
        call line_height
        mov QWORD[rbp-16], rax
        cmp rax, 0
        je .loop_end
        add rsp, 16

        mov rcx, QWORD[rbp+24]
        add rcx, -1
        push rcx
        push rcx
        push QWORD[rbp-8]
        call does_line_not_have_marker
        add rsp, 104
        cmp rax, 0
        je .return_false
        add rsp, -104

        mov rcx, QWORD[rbp-16]
        cmp rcx, QWORD[rbp-24]
        je .loop

        mov rcx, QWORD[rbp-40]
        add rsp, 104
        cmp rcx, 0
        jne .return_false
        add rsp, -104

        mov QWORD[rbp-40], 1
        mov rcx, QWORD[rbp-16]
        mov QWORD[rbp-24], rcx
        mov rcx, QWORD[rbp-8]
        mov QWORD[rbp-48], rcx

        jmp .loop
    .loop_end:

    mov rcx, QWORD[rbp-40]
    add rsp, 96
    cmp rcx, 0
    je .return_false
    add rsp, -80

    mov rcx, QWORD[rbp-32]
    add rcx, QWORD[rbp+24]
    add rcx, -1
    push rcx
    mov rcx, QWORD[rbp-24]
    add rcx, QWORD[rbp+24]
    push rcx
    push QWORD[rbp-48]
    call does_line_not_have_marker
    add rsp, 104
    cmp rax, 0
    je .return_false
    add rsp, -80

    mov rcx, QWORD[rbp-24]
    add rcx, QWORD[rbp+24]
    add rcx, -1
    push rcx
    push QWORD[rbp+24]
    push QWORD[rbp-8]
    call does_line_not_have_marker
    add rsp, 104
    cmp rax, 0
    je .return_false
    add rsp, -80

    mov rcx, QWORD[rbp-8]
    sub rcx, QWORD[rbp+16]
    mov rax, QWORD[rbp-32]
    mov rsi, 2
    div rsi
    add rsp, 80
    cmp eax, ecx
    jne .return_false
    add rsp, -80

    mov rcx, QWORD[rbp-48]
    sub rcx, QWORD[rbp+16]
    add rsp, 80
    cmp rcx, QWORD[rbp-24]
    jne .return_false

.return_true:
    mov rax, 1
    mov rsp, rbp
    pop rbp
    ret
.return_false:
    mov rax, 0
    mov rsp, rbp
    pop rbp
    ret