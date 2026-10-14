// ===========================================================================
// 07 - El intercambio que no intercambia
// Bloque 3 (25 min) - Paso de argumentos por valor
//
// OBJETIVO
//   Mostrar el limite del paso por valor con el ejemplo clasico: la logica de
//   la funcion es correcta y aun asi el resultado no sale de la funcion.
//
// REGLA
//   Una funcion con parametros por valor no puede modificar las variables de
//   quien la llamo.
//
// PARA LA EXPOSICION
//   NO dar aun la solucion. La respuesta llega en el bloque 5, con dos
//   simbolos & de mas. Dejar la pregunta escrita en el pizarron.
// ===========================================================================

#include <iostream>

void intercambia_mal(int a, int b) {
    std::cout << "  [dentro] al entrar: a = " << a << ", b = " << b << '\n';

    int temporal = a;
    a = b;
    b = temporal;

    std::cout << "  [dentro] al salir : a = " << a << ", b = " << b
              << "  <-- si se intercambiaron\n";
}  // ...y aqui mueren a y b, que eran copias

int main() {
    int x = 1;
    int y = 2;

    std::cout << "[antes]   x = " << x << ", y = " << y << '\n';
    intercambia_mal(x, y);
    std::cout << "[despues] x = " << x << ", y = " << y << "  <-- NO cambiaron\n\n";

    std::cout << "La funcion SI intercambia... sus propias copias.\n"
              << "Al terminar, esas copias desaparecen.\n\n"
              << "PREGUNTA ABIERTA: que necesita la funcion para modificar\n"
              << "las variables de main?\n";
    return 0;
}
