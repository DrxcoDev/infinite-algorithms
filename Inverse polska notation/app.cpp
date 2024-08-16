#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <stdexcept>

// Función para evaluar operaciones básicas
double aplicarFuncion(const std::string& funcion, double a, double b) {
    if (funcion == "+") return a + b;
    if (funcion == "-") return a - b;
    if (funcion == "*") return a * b;
    if (funcion == "/") return a / b;
    throw std::invalid_argument("Operador desconocido: " + funcion);
}

// Función para verificar si una cadena es un operador
bool esOperador(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// Función para verificar si una cadena es un número
bool esNumero(const std::string& token) {
    std::istringstream iss(token);
    double valor;
    return (iss >> valor) && iss.eof();
}

// Función principal para evaluar la expresión en notación postfija
double evaluarExpresionPostfija(const std::vector<std::string>& bandejaEntrada) {
    std::stack<double> pila;

    for (const auto& elemento : bandejaEntrada) {
        if (esNumero(elemento)) {
            pila.push(std::stod(elemento)); // Si es un número, lo ponemos en la pila
        } else if (esOperador(elemento)) {
            if (pila.size() < 2) {
                throw std::runtime_error("Error: No hay suficientes argumentos en la pila para la operación.");
            }
            // Tomar los últimos dos operandos de la pila
            double operando2 = pila.top(); pila.pop();
            double operando1 = pila.top(); pila.pop();

            // Evaluar la función (operador)
            double resultado = aplicarFuncion(elemento, operando1, operando2);

            // Introducir el resultado en la pila
            pila.push(resultado);
        } else {
            throw std::invalid_argument("Elemento desconocido en la bandeja de entrada: " + elemento);
        }
    }

    if (pila.size() == 1) {
        return pila.top(); // El valor es el resultado del cálculo
    } else {
        throw std::runtime_error("Error: El usuario ha introducido demasiados elementos.");
    }
}

int main() {
    try {
        // Ejemplo de bandeja de entrada (expresión postfija)
        std::vector<std::string> bandejaEntrada = {"3", "4", "+", "2", "*", "7", "/"};

        double resultado = evaluarExpresionPostfija(bandejaEntrada);
        std::cout << "Resultado: " << resultado << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    // Pausa para que el programa no se cierre inmediatamente
    std::cout << "Presiona Enter para salir...";
    std::cin.get();

    return 0;
}
