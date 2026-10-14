// ===========================================================================
// 13 - Arreglos: declaracion, inicializacion y recorrido
// Bloque 7 (25 min) - Arreglos unidimensionales
//
// OBJETIVO
//   Un arreglo es un bloque CONTIGUO de N objetos del mismo tipo, con N fijo
//   y conocido en tiempo de compilacion. Ese "contiguo" y ese "fijo" explican
//   casi todo lo demas: la velocidad, el indice base cero y sus limitaciones.
//
// NORMA (ISO/IEC 14882, [dcl.array]/1)
//   En 'T D[expresion-constante]' la expresion debe ser una expresion
//   constante convertida de tipo std::size_t y su valor N debe ser mayor que
//   cero. Por eso no se puede escribir 'int v[n]' con n leido del usuario:
//   eso es un arreglo de longitud variable (VLA), extension de C99 que C++
//   NO incluye. La alternativa correcta es std::vector.
//
// INDICES
//   Validos: 0 .. N-1. El indice se traduce a una direccion:
//       &v[i] == (direccion base de v) + i * sizeof(T)
// ===========================================================================

#include <iomanip>
#include <iostream>
#include <iterator>  // std::size (C++17)

int main() {
    // --- Formas de declarar e inicializar ----------------------------------
    int a[5] = {10, 20, 30, 40, 50};  // tamaño y valores explicitos
    int b[5] = {1, 2};                // los que faltan se inicializan a 0
    int c[5] = {};                    // los cinco a 0
    int d[] = {7, 8, 9};              // el tamaño lo deduce el compilador: 3
    int sin_inicializar[3];           // valores INDETERMINADOS: leerlos es UB

    sin_inicializar[0] = 1;  // hay que darles valor antes de leerlos
    sin_inicializar[1] = 2;
    sin_inicializar[2] = 3;

    // int n = 5; int malo[n];   // NO es C++ estandar (VLA). Usa std::vector.

    auto imprime = [](const char* etiqueta, const int* v, std::size_t n) {
        std::cout << "  " << std::left << std::setw(18) << etiqueta << "[ ";
        for (std::size_t i = 0; i < n; ++i) {
            std::cout << v[i] << ' ';
        }
        std::cout << "]\n";
    };

    std::cout << "Inicializacion\n";
    imprime("a[5] = {10..50}", a, 5);
    imprime("b[5] = {1,2}", b, 5);
    imprime("c[5] = {}", c, 5);
    imprime("d[] = {7,8,9}", d, 3);
    imprime("sin_inicializar", sin_inicializar, 3);

    // --- Tamaño -------------------------------------------------------------
    std::cout << "\nTamaño del arreglo 'a'\n"
              << "  sizeof(a)              = " << sizeof(a) << " bytes (los 5 enteros)\n"
              << "  sizeof(a[0])           = " << sizeof(a[0]) << " bytes\n"
              << "  sizeof(a)/sizeof(a[0]) = " << sizeof(a) / sizeof(a[0]) << " elementos\n"
              << "  std::size(a)           = " << std::size(a) << " elementos  (C++17, preferible)\n";

    // --- Contiguidad --------------------------------------------------------
    std::cout << "\nLos elementos son contiguos en memoria\n";
    for (std::size_t i = 0; i < std::size(a); ++i) {
        std::cout << "  &a[" << i << "] = " << &a[i] << "   diferencia con a[0]: "
                  << reinterpret_cast<const char*>(&a[i]) - reinterpret_cast<const char*>(&a[0])
                  << " bytes\n";
    }

    // --- Recorrido ----------------------------------------------------------
    std::cout << "\nRecorrido clasico con indice (0 .. N-1)\n  ";
    for (std::size_t i = 0; i < std::size(a); ++i) {
        std::cout << "a[" << i << "]=" << a[i] << "  ";
    }

    std::cout << "\n\nRecorrido con for basado en rango (C++11); no hay indices que equivocar\n  ";
    for (int valor : a) {
        std::cout << valor << ' ';
    }

    std::cout << "\n\nModificar dentro del for necesita referencia\n  ";
    for (int& valor : a) {  // sin el & se modificaria una copia
        valor *= 2;
    }
    for (int valor : a) {
        std::cout << valor << ' ';
    }
    std::cout << "\n\nRESUMEN: tamaño fijo en tiempo de compilacion, memoria contigua,\n"
              << "indices de 0 a N-1, y ninguna comprobacion automatica de limites.\n";
    return 0;
}
