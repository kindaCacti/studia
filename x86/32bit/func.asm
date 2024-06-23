section .text
global start_data_offset
global read_pixel
global line_height
global does_line_not_have_marker
global is_marker
global check_marker

check_marker:
    push ebp
    mov ebp, esp

    mov esi, DWORD[ebp+16]
    push esi

    xor eax, eax
    mov al, BYTE[esi+23]
    shl eax, 8
    mov al, BYTE[esi+22]
    push eax

    xor eax, eax
    mov al, BYTE[esi+19]
    shl eax, 8
    mov al, BYTE[esi+18]
    push eax

    xor eax, eax
    mov al, BYTE[esi+10]
    push eax

    mov esi, DWORD[ebp+12]
    push DWORD[esi]
    mov esi, DWORD[ebp+8]
    push DWORD[esi]
    call is_marker
    add esp, 24

    mov esp, ebp
    pop ebp
    ret

start_data_offset:
    push ebp
    mov ebp, esp
    mov esi, [ebp+8]
    xor eax, eax            ; clear eax
    mov al, BYTE[esi+10]
    mov esp, ebp
    pop ebp
    ret

read_pixel:
    push ebp
    mov ebp, esp
    mov ecx, DWORD[ebp+8]        ; ecx = x_coordinate
    mov esi, DWORD[ebp+24]       ; esi = height
    mov eax, DWORD[ebp+12]       ; eax = y_coordinate
    sub esi, eax            ; esi -= eax
    sub esi, 1              ; esi -= 1 (we now reversed the y coordinate)
    mov eax, DWORD[ebp+20]       ; eax = width
    mul esi                 ; esi *= width
    mov esi, eax
    add ecx, esi            ; ecx += vectically_skipped_pixels
    mov eax, 3
    mul ecx                 ; byte_offset = pixel_id * 3 (3 bytes per pixel)
    mov ecx, eax
    xor eax, eax
    mov al, BYTE[ebp+16]    ; eax = data_start_offset
    add ecx, eax            ; byte_offset += data_start_offset
    mov esi, [ebp+28]        ; esi = data_pointer
    add esi, ecx            ; data_pointer += byte_offset
    xor eax, eax            ; clear eax
    mov al, BYTE[esi]       ; first 8 bits of eax = blue value
    shl eax, 8              ; shift left by 8 bits
    mov al, BYTE[esi+1]     ; first 8 bits of eax = green value
    shl eax, 8              ; shift left by 8 bits
    mov al, BYTE[esi+2]     ; first 8 bits of eax = red value
    mov esp, ebp
    pop ebp
    ret

line_height:
    push ebp
    mov ebp, esp
    xor ecx, ecx            ; ecx = 0 // line_height
    mov esi, DWORD[ebp+12]       ; esi = current_y
    .loop:
        mov eax, DWORD[ebp+24]
        cmp esi, eax
        jge .loop_end
        push ecx
        push DWORD[ebp+28]
        push DWORD[ebp+24]
        push DWORD[ebp+20]
        push DWORD[ebp+16]
        push esi
        push DWORD[ebp+8]
        call read_pixel
        pop esi
        pop esi
        add esp, 16
        pop ecx
        cmp eax, 0
        jne .loop_end
        inc esi
        inc ecx
        jmp .loop
    .loop_end:
    mov eax, ecx
    mov esp, ebp
    pop ebp
    ret

does_line_not_have_marker:
    push ebp
    mov ebp, esp
    mov ecx, DWORD[ebp+8]
    mov eax, DWORD[ebp+24]
    cmp ecx, eax
    jge .return_true
    mov eax, 0
    cmp ecx, eax
    jl .return_true
    mov esi, DWORD[ebp+8]
    mov eax, 0
    cmp esi, eax
    jl .return_true
    mov ecx, DWORD[ebp+12]
    .loop:
        mov esi, DWORD[ebp+16]
        cmp ecx, esi
        jg .return_true
        push DWORD[ebp+32]
        push DWORD[ebp+28]
        push DWORD[ebp+24]
        push DWORD[ebp+20]
        push ecx
        push DWORD[ebp+8]
        call read_pixel
        add esp, 24
        cmp eax, 0
        je .return_false
        mov ecx, DWORD[ebp+12]
        inc ecx
        mov DWORD[ebp+12], ecx
        jmp .loop
.return_true:
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
.return_false:
    mov eax, 0    
    mov esp, ebp
    pop ebp
    ret

; extern int isMarker(int x, int y, int data_offset, int width, int height, unsigned char* data);
is_marker:
    push ebp
    mov ebp, esp
    push DWORD[ebp+28]
    push DWORD[ebp+24]
    push DWORD[ebp+20]
    push DWORD[ebp+16]
    push DWORD[ebp+12]
    push DWORD[ebp+8]
    call read_pixel
    add esp, 24
    cmp eax, 0
    jne .return_false
    add esp, -24

    add esp, 8
    mov ecx, DWORD[ebp+12]
    add ecx, -1
    push ecx
    push ecx
    push DWORD[ebp+8]
    call does_line_not_have_marker
    add esp, 28
    cmp eax, 0
    je .return_false
    add esp, -28

    add esp, 12
    push DWORD[ebp+12]
    push DWORD[ebp+8]
    call line_height
    add esp, 24
    push DWORD[ebp+8]   ; current_x [ebp-4]
    push eax            ; current_height [ebp-8]
    push eax            ; last_height [ebp-12]
    push eax            ; best_height [ebp-16]
    push 0              ; has_step [ebp-20]
    push -1             ; step_x [ebp-24]

    mov ecx, DWORD[ebp+8]
    add ecx, -1
    mov esi, DWORD[ebp+12]
    add esi, DWORD[ebp-8]
    dec esi
    push DWORD[ebp+28]
    push DWORD[ebp+24]
    push DWORD[ebp+20]
    push DWORD[ebp+16]
    push esi
    push DWORD[ebp+12]
    push ecx
    call does_line_not_have_marker
    add esp, 52
    cmp eax, 0
    je .return_false
    add esp, -52

    .loop:
        mov ecx, DWORD[ebp-4]
        inc ecx
        mov DWORD[ebp-4], ecx
        add esp, 4
        cmp ecx, DWORD[ebp+20]
        jge .loop_end
        add esp, 8

        push DWORD[ebp+12]
        push DWORD[ebp-4]
        call line_height
        mov DWORD[ebp-8], eax
        cmp eax, 0
        je .loop_end
        add esp, 8

        mov ecx, DWORD[ebp+12]
        add ecx, -1
        push ecx
        push ecx
        push DWORD[ebp-4]
        call does_line_not_have_marker
        add esp, 52
        cmp eax, 0
        je .return_false
        add esp, -52

        mov ecx, DWORD[ebp-8]
        cmp ecx, DWORD[ebp-12]
        je .loop

        mov ecx, DWORD[ebp-20]
        add esp, 52
        cmp ecx, 0
        jne .return_false
        add esp, -52

        mov DWORD[ebp-20], 1
        mov ecx, DWORD[ebp-8]
        mov DWORD[ebp-12], ecx
        mov ecx, DWORD[ebp-4]
        mov DWORD[ebp-24], ecx

        jmp .loop
    .loop_end:

    mov ecx, DWORD[ebp-20]
    add esp, 48
    cmp ecx, 0
    je .return_false
    add esp, -40

    mov ecx, DWORD[ebp-16]
    add ecx, DWORD[ebp+12]
    add ecx, -1
    push ecx
    mov ecx, DWORD[ebp-12]
    add ecx, DWORD[ebp+12]
    push ecx
    push DWORD[ebp-24]
    call does_line_not_have_marker
    add esp, 52
    cmp eax, 0
    je .return_false
    add esp, -40

    mov ecx, DWORD[ebp-12]
    add ecx, DWORD[ebp+12]
    add ecx, -1
    push ecx
    push DWORD[ebp+12]
    push DWORD[ebp-4]
    call does_line_not_have_marker
    add esp, 52
    cmp eax, 0
    je .return_false
    add esp, -40

    mov ecx, DWORD[ebp-4]
    sub ecx, DWORD[ebp+8]
    mov eax, DWORD[ebp-16]
    mov esi, 2
    div esi
    add esp, 40
    cmp eax, ecx
    jne .return_false
    add esp, -40

    mov ecx, DWORD[ebp-24]
    sub ecx, DWORD[ebp+8]
    add esp, 40
    cmp ecx, DWORD[ebp-12]
    jne .return_false

.return_true:
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
.return_false:
    mov eax, 0
    mov esp, ebp
    pop ebp
    ret