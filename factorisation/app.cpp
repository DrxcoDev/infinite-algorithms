#include <iostream>

// Función para encontrar los factores primos de un número n
void factorizar(int n) {
    // Dividir por 2 hasta que n sea impar
    while (n % 2 == 0) {
        std::cout << 2 << " ";
        n /= 2;
    }

    // n debe ser impar ahora. Se comienza desde 3 y se salta de 2 en 2 (solo números impares)
    for (int i = 3; i * i <= n; i += 2) {
        // Mientras i divide a n, imprimimos i y dividimos n
        while (n % i == 0) {
            std::cout << i << " ";
            n /= i;
        }
    }

    // Esto se maneja para el caso cuando n es un número primo mayor que 2
    if (n > 2) {
        std::cout << n << " ";
    }

    std::cout << std::endl;
}

int main() {
    int numero;

    std::cout << "Introduce un número para factorizar: ";
    std::cin >> numero;

    std::cout << "Factores primos de " << numero << ": ";
    factorizar(numero);

    return 0;
}
