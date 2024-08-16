section .data
    n dq 60               ; Número a factorizar (ejemplo: 60)
    factor dq 2           ; Primer factor a probar
    result db "Factores primos: ", 0

section .bss
    temp resq 1           ; Espacio para almacenar temporalmente n

section .text
    global _start

_start:
    ; Copiar n a temp
    mov rax, [n]
    mov [temp], rax

    ; Imprimir el mensaje inicial
    mov rsi, result
    call print_string

    ; Dividir por 2 hasta que ya no sea divisible
div_loop:
    mov rax, [temp]
    mov rbx, [factor]
    xor rdx, rdx          ; Limpiar rdx antes de la división
    div rbx               ; rax = rax / rbx; rdx = rax % rbx

    test rdx, rdx         ; ¿Es divisible?
    jnz next_factor       ; Si no, probar con el siguiente factor

    ; Si es divisible, imprimir el factor
    call print_number

    ; Actualizar temp y repetir la división
    mov [temp], rax
    jmp div_loop

next_factor:
    ; Incrementar el factor en 1
    add qword [factor], 1

    ; Chequear si el cuadrado del factor es mayor que n
    mov rax, [factor]
    imul rax, rax
    cmp rax, [temp]
    jle div_loop

    ; Imprimir el número restante si es mayor que 2
    mov rax, [temp]
    cmp rax, 2
    jle done

    ; Imprimir el número restante
    call print_number

done:
    ; Salir del programa
    mov rax, 60           ; syscall: exit
    xor rdi, rdi          ; código de salida 0
    syscall

; Subrutina para imprimir un número (en decimal)
print_number:
    mov rbx, 10           ; Base 10
print_loop:
    xor rdx, rdx
    div rbx               ; Divide rax entre 10, cociente en rax, resto en rdx
    add dl, '0'           ; Convertir el dígito a ASCII
    push rdx              ; Almacenar en la pila
    test rax, rax         ; ¿Es el cociente 0?
    jnz print_loop        ; Si no, continuar dividiendo

print_digit:
    pop rax
    call print_char
    test rsp, rsp
    jnz print_digit

    mov rax, 32           ; Imprimir un espacio
    call print_char
    ret

; Subrutina para imprimir una cadena de caracteres
print_string:
    mov rdx, rsi          ; Puntero a la cadena
    call print_char
    ret

; Subrutina para imprimir un carácter
print_char:
    mov rdi, 1            ; file descriptor 1 es stdout
    mov rsi, rdx          ; Dirección del carácter a imprimir
    mov rdx, 1            ; Longitud 1
    mov rax, 1            ; syscall: write
    syscall
    ret
