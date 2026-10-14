// ===========================================================================
// 05 - Que ocurre en la memoria cuando se llama a una funcion
// Bloque 2 (10 min) - Como viaja un argumento
//
// OBJETIVO
//   Ver que cada llamada reserva su propio espacio (su marco) y que al
//   terminar, ese espacio se libera y se reutiliza.
//
// REGLA
//   Los parametros y las variables locales viven en la PILA. Una llamada
//   apila su marco; al volver, lo desapila.
//
// PARA LA EXPOSICION
//   Ejecutarlo dos veces: los numeros cambian, pero la RELACION entre ellos
//   (cada nivel mas abajo) no cambia.
// ===========================================================================

#include <iostream>

void nivel_3(int profundidad) {
    int local = 33;
    std::cout << "      nivel_3: parametro en " << &profundidad
              << "  local en " << &local << '\n';
}

void nivel_2(int profundidad) {
    int local = 22;
    std::cout << "    nivel_2: parametro en " << &profundidad
              << "  local en " << &local << '\n';
    nivel_3(profundidad + 1);
}

void nivel_1(int profundidad) {
    int local = 11;
    std::cout << "  nivel_1: parametro en " << &profundidad
              << "  local en " << &local << '\n';
    nivel_2(profundidad + 1);
}

int main() {
    int local_main = 1;
    std::cout << "main: local en " << &local_main << "\n\n";

    std::cout << "Primera cadena de llamadas:\n";
    nivel_1(1);

    std::cout << "\nSegunda cadena de llamadas (las anteriores ya terminaron):\n";
    nivel_1(1);

    std::cout << "\nCONCLUSION: las direcciones BAJAN conforme se anidan las llamadas.\n"
              << "Las dos cadenas usan la misma memoria: al volver, el marco se libera.\n"
              << "El parametro es una variable local mas de ese marco.\n";
    return 0;
}
