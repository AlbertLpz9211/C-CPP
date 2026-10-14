// ===========================================================================
// 03 - El intercambio que no intercambia
// Bloque 2 (30 min) - Paso de argumentos por valor
//
// OBJETIVO
//   El ejemplo canonico del limite del paso por valor. La funcion es
//   logicamente correcta: intercambia sus dos variables. El problema es que
//   intercambia SUS COPIAS, y al volver esas copias se destruyen.
//
// USO EN CLASE
//   Este archivo es la motivacion para el bloque de referencias. Conviene
//   dejar la pregunta abierta: "la logica esta bien, entonces, que falla?"
//   La respuesta esta en 07_swap_por_referencia.cpp.
// ===========================================================================

#include <iostream>

// La logica del intercambio es correcta... para las variables locales.
void intercambia_mal(int a, int b) {
    std::cout << "  [dentro]  al entrar : a=" << a << " b=" << b << '\n';

    int temporal = a;
    a = b;
    b = temporal;

    std::cout << "  [dentro]  al salir  : a=" << a << " b=" << b << "  <-- si funciono aqui\n";
}  // Aqui mueren 'a' y 'b'. Nadie se entera del intercambio.

int main() {
    int x = 1;
    int y = 2;

    std::cout << "Antes de llamar : x=" << x << " y=" << y << '\n';
    intercambia_mal(x, y);
    std::cout << "Despues de llamar: x=" << x << " y=" << y << "  <-- sin cambios\n\n";

    std::cout << "DIAGNOSTICO\n"
              << "  La funcion recibio COPIAS de x e y. Intercambio las copias.\n"
              << "  Al terminar la funcion, el marco de pila se libera y las copias\n"
              << "  desaparecen. x e y nunca fueron tocadas.\n\n"
              << "  Para modificar los argumentos del llamador hace falta que la\n"
              << "  funcion sepa DONDE viven: eso son las referencias y los punteros.\n";
    return 0;
}
