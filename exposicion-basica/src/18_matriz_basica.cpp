// ===========================================================================
// 18 - Arreglos bidimensionales: filas y columnas
// Bloque 10 (15 min) - Arreglos bidimensionales
//
// OBJETIVO
//   Ver que int m[3][4] es un arreglo de 3 arreglos de 4 enteros, guardado
//   como un unico bloque contiguo, fila tras fila.
//
// REGLA
//   m[i][j] : i es la fila, j es la columna. Se recorre con dos for anidados.
//
// PARA LA EXPOSICION
//   Dibujar la cuadricula en el pizarron y numerar las casillas en el orden
//   en que estan en memoria: 0..11.
// ===========================================================================

#include <iostream>

int main() {
    const int FILAS = 3;
    const int COLUMNAS = 4;

    int m[FILAS][COLUMNAS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // --- Recorrido con dos bucles anidados ---------------------------------
    std::cout << "La matriz:\n";
    for (int i = 0; i < FILAS; ++i) {
        std::cout << "  ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << m[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // --- En memoria esta en una sola tira ----------------------------------
    std::cout << "En memoria, fila tras fila:\n  ";
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << m[i][j] << ' ';
        }
    }
    std::cout << "\n\n";

    std::cout << "Posicion de cada elemento contando desde el principio:\n";
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << "  m[" << i << "][" << j << "] = " << m[i][j]
                      << "   posicion " << i * COLUMNAS + j << '\n';
        }
    }
    std::cout << "\nLa formula es:  posicion = fila * COLUMNAS + columna\n\n";

    // --- Tamanos -----------------------------------------------------------
    std::cout << "sizeof(m)       = " << sizeof(m) << " bytes (toda la matriz)\n";
    std::cout << "sizeof(m[0])    = " << sizeof(m[0]) << " bytes (UNA FILA entera)\n";
    std::cout << "sizeof(m[0][0]) = " << sizeof(m[0][0]) << " bytes (un elemento)\n\n";

    // --- Suma por filas ----------------------------------------------------
    for (int i = 0; i < FILAS; ++i) {
        int suma = 0;
        for (int j = 0; j < COLUMNAS; ++j) {
            suma = suma + m[i][j];
        }
        std::cout << "suma de la fila " << i << " = " << suma << '\n';
    }

    std::cout << "\nCONCLUSION: m[i] no es un elemento, es una FILA COMPLETA.\n"
              << "De ahi salen todas las reglas del tema.\n";
    return 0;
}
