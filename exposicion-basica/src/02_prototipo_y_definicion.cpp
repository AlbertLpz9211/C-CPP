// ===========================================================================
// 02 - Prototipo (declaracion) y definicion
// Bloque 1 (30 min) - Funciones
//
// OBJETIVO
//   Explicar por que a veces la funcion aparece dos veces en el archivo: una
//   como prototipo antes de main y otra como definicion completa despues.
//
// REGLA
//   El compilador lee el archivo de arriba abajo. Para llamar a una funcion
//   necesita conocer ya su nombre, su tipo de retorno y sus parametros.
//   El prototipo da esa informacion y termina en punto y coma.
//
// PARA LA EXPOSICION
//   Comentar el prototipo y compilar: "use of undeclared identifier".
// ===========================================================================

#include <iostream>

// --- Prototipos: que existe y como se llama --------------------------------
int  mayor(int a, int b);          // termina en ';' y no lleva cuerpo
void imprime_linea(int longitud);
bool es_par(int n);

// Los nombres de los parametros en el prototipo son opcionales:
//   int mayor(int, int);
// Se escriben de todos modos porque documentan la funcion.

int main() {
    imprime_linea(40);

    std::cout << "mayor(12, 7) = " << mayor(12, 7) << '\n';
    std::cout << "mayor(-3, 5) = " << mayor(-3, 5) << '\n';

    int n = 10;
    if (es_par(n)) {
        std::cout << n << " es par\n";
    } else {
        std::cout << n << " es impar\n";
    }

    imprime_linea(40);
    return 0;
}

// --- Definiciones: como funciona cada una ----------------------------------
int mayor(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

void imprime_linea(int longitud) {
    for (int i = 0; i < longitud; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';
    // Una funcion void no devuelve nada: no lleva return con valor.
}

bool es_par(int n) {
    return n % 2 == 0;
}
