// ===========================================================================
// 01 - Que es una funcion: definirla, llamarla y devolver un resultado
// Bloque 1 (30 min) - Funciones
//
// OBJETIVO
//   Mostrar las tres partes de una funcion: tipo de retorno, nombre y lista
//   de parametros; y la diferencia entre DEFINIR una funcion y LLAMARLA.
//
// REGLA
//   Una funcion es un bloque de codigo con nombre. Recibe datos por sus
//   parametros y devuelve un resultado con return.
//
// PARA LA EXPOSICION
//   Escribir la funcion en vivo, compilar, y solo despues llamarla desde main.
// ===========================================================================

#include <iostream>

// Definicion de la funcion:
//
//   int        <- tipo del valor que devuelve
//   suma       <- nombre
//   (int a, int b)  <- lista de parametros
//
int suma(int a, int b) {
    int resultado = a + b;
    return resultado;  // devuelve el valor al que llamo la funcion
}

// Una funcion puede devolver el resultado de una expresion directamente.
double area_rectangulo(double base, double altura) {
    return base * altura;
}

int main() {
    std::cout << "Definir una funcion no ejecuta nada.\n";
    std::cout << "El codigo de suma() corre solo cuando se la llama.\n\n";

    int total = suma(3, 4);  // llamada: 3 y 4 son los ARGUMENTOS
    std::cout << "suma(3, 4)          = " << total << '\n';

    // La llamada se puede usar en medio de una expresion.
    std::cout << "suma(10, 20) + 5    = " << suma(10, 20) + 5 << '\n';

    // Los argumentos pueden ser variables o expresiones.
    int x = 7;
    int y = 8;
    std::cout << "suma(x, y)          = " << suma(x, y) << '\n';
    std::cout << "suma(x + 1, y * 2)  = " << suma(x + 1, y * 2) << '\n';

    std::cout << "area_rectangulo(2.5, 4.0) = " << area_rectangulo(2.5, 4.0) << '\n';

    std::cout << "\nCONCLUSION: la funcion es una receta con nombre.\n"
              << "Se escribe una vez y se usa tantas veces como haga falta.\n";
    return 0;
}
