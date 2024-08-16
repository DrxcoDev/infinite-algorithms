#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función para evaluar operaciones básicas
double aplicarFuncion(const char* funcion, double a, double b) {
    if (strcmp(funcion, "+") == 0) return a + b;
    if (strcmp(funcion, "-") == 0) return a - b;
    if (strcmp(funcion, "*") == 0) return a * b;
    if (strcmp(funcion, "/") == 0) return a / b;
    fprintf(stderr, "Operador desconocido: %s\n", funcion);
    exit(EXIT_FAILURE);
}

// Función para verificar si una cadena es un operador
int esOperador(const char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}

// Función para verificar si una cadena es un número
int esNumero(const char* token) {
    char* endptr;
    strtod(token, &endptr);
    return (*endptr == '\0');
}

// Función principal para evaluar la expresión en notación postfija
double evaluarExpresionPostfija(const char* bandejaEntrada[], int tamaño) {
    double pila[100];
    int pilaTop = -1;

    for (int i = 0; i < tamaño; i++) {
        const char* elemento = bandejaEntrada[i];

        if (esNumero(elemento)) {
            pila[++pilaTop] = strtod(elemento, NULL); // Si es un número, lo ponemos en la pila
        } else if (esOperador(elemento)) {
            if (pilaTop < 1) {
                fprintf(stderr, "Error: No hay suficientes argumentos en la pila para la operación.\n");
                exit(EXIT_FAILURE);
            }
            // Tomar los últimos dos operandos de la pila
            double operando2 = pila[pilaTop--];
            double operando1 = pila[pilaTop--];

            // Evaluar la función (operador)
            double resultado = aplicarFuncion(elemento, operando1, operando2);

            // Introducir el resultado en la pila
            pila[++pilaTop] = resultado;
        } else {
            fprintf(stderr, "Elemento desconocido en la bandeja de entrada: %s\n", elemento);
            exit(EXIT_FAILURE);
        }
    }

    if (pilaTop == 0) {
        return pila[pilaTop]; // El valor es el resultado del cálculo
    } else {
        fprintf(stderr, "Error: El usuario ha introducido demasiados elementos.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Ejemplo de bandeja de entrada (expresión postfija)
    const char* bandejaEntrada[] = {"3", "4", "+", "2", "*", "7", "/"};
    int tamaño = sizeof(bandejaEntrada) / sizeof(bandejaEntrada[0]);

    double resultado = evaluarExpresionPostfija(bandejaEntrada, tamaño);
    printf("Resultado: %.2f\n", resultado);

    // Pausa para que el programa no se cierre inmediatamente
    printf("Presiona Enter para salir...");
    getchar();

    return 0;
}
