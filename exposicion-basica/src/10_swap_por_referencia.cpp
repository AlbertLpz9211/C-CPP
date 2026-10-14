// ===========================================================================
// 10 - El mismo cuerpo, dos simbolos &, otro resultado
// Bloque 5 (30 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Cerrar la pregunta abierta del bloque 3: el intercambio que si funciona.
//
// REGLA
//   Con un parametro int&, el parametro NO es una variable nueva: es otro
//   nombre para el argumento del llamador. Modificarlo modifica el original.
//
// PARA LA EXPOSICION
//   Mostrar las dos funciones lado a lado. El cuerpo es identico.
// ===========================================================================

#include <iostream>

void intercambia_mal(int a, int b) {
    int temporal = a;
    a = b;
    b = temporal;
}

void intercambia(int& a, int& b) {  // <-- toda la diferencia esta aqui
    int temporal = a;
    a = b;
    b = temporal;
}

void muestra_direcciones(int& a) {
    std::cout << "  el parametro por referencia vive en " << &a << '\n';
}

int main() {
    int x = 1;
    int y = 2;

    std::cout << "Version por VALOR\n";
    std::cout << "  [antes]   x = " << x << ", y = " << y << '\n';
    intercambia_mal(x, y);
    std::cout << "  [despues] x = " << x << ", y = " << y << "  <-- sin efecto\n\n";

    std::cout << "Version por REFERENCIA\n";
    std::cout << "  [antes]   x = " << x << ", y = " << y << '\n';
    intercambia(x, y);
    std::cout << "  [despues] x = " << x << ", y = " << y << "  <-- intercambiadas\n\n";

    std::cout << "x vive en " << &x << '\n';
    muestra_direcciones(x);
    std::cout << "Es la misma direccion: el parametro y x son la misma variable.\n\n";

    std::cout << "OJO: la llamada se escribe igual en los dos casos, intercambia(x, y).\n"
              << "La unica forma de saber que pasa es LEER LA FIRMA de la funcion.\n";
    return 0;
}
