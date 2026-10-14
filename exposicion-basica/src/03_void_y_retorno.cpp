// ===========================================================================
// 03 - Funciones void, valor de retorno y varios parametros
// Bloque 1 (30 min) - Funciones
//
// OBJETIVO
//   Distinguir la funcion que CALCULA un valor (devuelve algo) de la que
//   HACE algo (void), y mostrar que una funcion puede tener varios return.
//
// REGLA
//   return termina la funcion en el acto. El codigo que queda debajo no se
//   ejecuta.
//
// PARA LA EXPOSICION
//   Preguntar que devuelve clasifica(0) antes de ejecutarlo.
// ===========================================================================

#include <iostream>

// Funcion que devuelve un valor: se usa dentro de una expresion.
double promedio(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

// Funcion void: hace algo (imprimir) pero no devuelve ningun valor.
void saluda(int veces) {
    for (int i = 1; i <= veces; ++i) {
        std::cout << "  Hola numero " << i << '\n';
    }
    // Se puede usar 'return;' a secas para salir antes de tiempo.
}

// Varios return: el primero que se ejecuta termina la funcion.
int clasifica(int n) {
    if (n < 0) {
        return -1;  // negativo
    }
    if (n == 0) {
        return 0;  // cero
    }
    return 1;  // positivo
}

// Salida temprana: se comprueba el caso malo al principio.

double division_segura(double a, double b) {
    if (b == 0.0) {
        std::cout << "  [aviso] division entre cero; devuelvo 0\n";
        return 0.0;
    }
    return a / b;
}


int main() {
    std::cout << "promedio(8, 9, 10) = " << promedio(8, 9, 10) << "\n\n";

    std::cout << "saluda(3) no devuelve nada, solo imprime:\n";
    saluda(3);
    std::cout << '\n';

    std::cout << "clasifica(-5) = " << clasifica(-5) << '\n';
    std::cout << "clasifica( 0) = " << clasifica(0) << '\n';
    std::cout << "clasifica( 7) = " << clasifica(7) << "\n\n";

    std::cout << "division_segura(10, 4) = " << division_segura(10, 4) << '\n';
    std::cout << "division_segura(10, 0) = " << division_segura(10, 0) << '\n';

    std::cout << "\nCONCLUSION: si la funcion produce un dato, devuelvelo con return.\n"
              << "Si solo realiza una accion, declarala void.\n";
    return 0;
}


