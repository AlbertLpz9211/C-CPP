// ===========================================================================
// 14 - Arreglos: declarar, inicializar y recorrer
// Bloque 8 (25 min) - Arreglos unidimensionales
//
// OBJETIVO
//   Ver que un arreglo es un bloque contiguo de N variables del mismo tipo y
//   que el indice es un desplazamiento desde el principio.
//
// REGLA
//   int v[5];  reserva 5 enteros seguidos. Los indices validos van de 0 a 4.
//
// PARA LA EXPOSICION
//   Detenerse en la tabla de direcciones: la diferencia entre una y la
//   siguiente es siempre sizeof(int) = 4 bytes.
// ===========================================================================

#include <iostream>

int main() {
    // --- Formas de inicializar ---------------------------------------------
    int a[5] = {10, 20, 30, 40, 50};  // los cinco valores
    int b[5] = {1, 2};                // 1 2 0 0 0: lo que falta se pone a cero
    int c[5] = {};                    // los cinco a cero
    int d[] = {7, 8, 9};              // tamano deducido: 3

    std::cout << "a: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << "\nb: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << "\nc: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << "\nd: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << d[i] << ' ';
    }
    std::cout << "\n\n";

    // --- El arreglo es un bloque contiguo -----------------------------------
    std::cout << "Direccion de cada elemento de a:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "  &a[" << i << "] = " << &a[i] << '\n';
    }
    std::cout << "Cada una esta " << sizeof(int) << " bytes despues de la anterior.\n\n";

    // --- Tamano --------------------------------------------------------------
    std::cout << "sizeof(a)            = " << sizeof(a) << " bytes (todo el arreglo)\n";
    std::cout << "sizeof(a[0])         = " << sizeof(a[0]) << " bytes (un elemento)\n";
    std::cout << "sizeof(a)/sizeof(a[0]) = " << sizeof(a) / sizeof(a[0])
              << " elementos\n\n";

    // --- El tamano debe ser constante ---------------------------------------
    const int N = 4;
    double temperaturas[N] = {21.5, 22.0, 19.8, 23.1};
    std::cout << "temperaturas: ";
    for (int i = 0; i < N; ++i) {
        std::cout << temperaturas[i] << ' ';
    }
    std::cout << "\n\n";

    // int n;  std::cin >> n;  int malo[n];   // NO es C++ estandar

    // --- Recorrido por rango (equivalente, sin indices) ---------------------
    std::cout << "recorrido por rango: ";
    for (int valor : a) {
        std::cout << valor << ' ';
    }
    std::cout << "\n\nCONCLUSION: el indice cuenta desde cero porque es un\n"
              << "DESPLAZAMIENTO desde el primer elemento, no una posicion.\n";
    return 0;
}
