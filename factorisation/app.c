#include <stdio.h>
#include <stdbool.h>

// Función para encontrar los factores primos de un número n
void factorizar(int n) {
    // Dividir por 2 hasta que n sea impar
    while (n % 2 == 0) {
        printf("%d ", 2);
        n /= 2;
    }

    // n debe ser impar ahora. Se comienza desde 3 y se salta de 2 en 2 (solo números impares)
    for (int i = 3; i * i <= n; i += 2) {
        // Mientras i divide a n, imprimimos i y dividimos n
        while (n % i == 0) {
            printf("%d ", i);
            n /= i;
        }
    }

    // Esto se maneja para el caso cuando n es un número primo mayor que 2
    if (n > 2) {
        printf("%d ", n);
    }

    printf("\n");
}

int main() {
    int numero;

    printf("Introduce un número para factorizar: ");
    scanf("%d", &numero);

    printf("Factores primos de %d: ", numero);
    factorizar(numero);

    return 0;
}
