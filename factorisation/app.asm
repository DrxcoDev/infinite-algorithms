section .data
    n dq 60               ; Number to factorize (example: 60)
    factor dq 2           ; First factor to test
    result db "Prime factors: ", 0

section .bss
    temp resq 1           ; Space to temporarily store n

section .text
    global _start

_start:
    ; Copy n to temp
    mov rax, [n]
    mov [temp], rax

    ; Print the initial message
    mov rsi, result
    call print_string

    ; Divide by 2 until it is no longer divisible
    mov rdi, 2
div_loop:
    mov rax, [temp]
    xor rdx, rdx          ; Clear rdx before division
    div rdi               ; rax = rax / rdi; rdx = rax % rdi

    test rdx, rdx         ; Is it divisible?
    jnz next_factor       ; If not, test the next factor

    ; If divisible, print the factor
    mov rsi, rdi
    call print_number

    ; Update temp and repeat division
    mov [temp], rax
    jmp div_loop

next_factor:
    ; Increment the factor by 1
    add rdi, 1

    ; Check if the square of the factor is greater than n
    mov rax, [temp]
    imul rax, rax
    cmp rax, [n]
    jle div_loop

    ; Print the remaining number if greater than 2
    mov rax, [temp]
    cmp rax, 2
    jle done

    ; Print the remaining number
    mov rsi, rax
    call print_number

done:
    ; Exit the program
    mov rax, 60           ; syscall: exit
    xor rdi, rdi          ; exit code 0
    syscall

; Subroutine to print a number (in decimal)
print_number:
    ; Convert number to ASCII decimal
    mov rbx, 10           ; Base 10
    mov rcx, rsi          ; Number to print
    mov rdx, 0            ; Reset digit index

    ; Find the number of digits
find_digits:
    xor rax, rax
    div rbx               ; Divide rcx by 10, quotient in rax, remainder in rdx
    push rdx              ; Store the digit on the stack
    test rcx, rcx         ; Are there more digits?
    jnz find_digits       ; If yes, continue

    ; Print the digits
print_digits:
    pop rax
    add al, '0'           ; Convert digit to ASCII
    mov rdi, 1            ; file descriptor 1 is stdout
    mov rsi, rax          ; Address of the character to print
    mov rdx, 1            ; Length 1
    mov rax, 1            ; syscall: write
    syscall
    test rsp, rsp
    jnz print_digits

    ; Print a space
    mov al, ' '
    mov rdi, 1
    mov rsi, rax
    mov rdx, 1
    mov rax, 1
    syscall

    ret

; Subroutine to print a string of characters
print_string:
    ; Print the string until the end
    mov rdi, 1            ; file descriptor 1 is stdout
    mov rax, 1            ; syscall: write
    mov rdx, 0            ; Length of the string
find_length:
    mov al, [rsi + rdx]  ; Read the next character
    test al, al           ; Is it the end of the string?
    jz print_string_end  ; If yes, finish
    inc rdx               ; Increase length
    jmp find_length

print_string_end:
    syscall
    ret
