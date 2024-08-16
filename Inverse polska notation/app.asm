section .data
    operand1 dq 3.0            ; Primer operando (3.0)
    operand2 dq 4.0            ; Segundo operando (4.0)
    result   dq 0.0            ; Resultado de la operación
    operator db '+'            ; Operador ('+')

section .text
    global _start

_start:
    ; Cargar los operandos en registros
    fld qword [operand1]       ; Cargar operand1 en la pila de la FPU
    fld qword [operand2]       ; Cargar operand2 en la pila de la FPU

    ; Realizar la operación basada en el operador
    mov al, [operator]
    cmp al, '+'                ; Comparar si el operador es '+'
    jne .error                 ; Si no es '+', ir a la sección de error
    fadd                       ; Sumar ST(0) y ST(1) y almacenar el resultado en ST(1)
    fstp qword [result]        ; Guardar el resultado en la memoria y liberar la pila de la FPU

    ; Preparar para la salida (imprimir resultado es complicado, omito aquí)
    mov rax, 60                ; syscall: exit
    xor rdi, rdi               ; código de salida 0
    syscall

.error:
    ; Manejo de errores (en este ejemplo, simplemente salimos)
    mov rax, 60                ; syscall: exit
    mov rdi, 1                 ; código de salida 1 (indica error)
    syscall
