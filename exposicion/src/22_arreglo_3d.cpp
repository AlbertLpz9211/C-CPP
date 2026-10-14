// ===========================================================================
// 22 - Tres dimensiones y la formula general
// Bloque 9 (25 min) - Arreglos multidimensionales
//
// OBJETIVO
//   Generalizar la idea: un arreglo de N dimensiones es un arreglo de
//   arreglos de (N-1) dimensiones. La formula del desplazamiento se extiende
//   igual que la de dos dimensiones.
//
//   Para T v[D0][D1][D2], el elemento v[i][j][k] esta en:
//       base + ( i*D1*D2 + j*D2 + k ) * sizeof(T)
//
//   Es exactamente lo que dice el ejemplo de la norma en [dcl.array]/9:
//   el primer indice se multiplica por el tamaño completo del objeto formado
//   por las dimensiones restantes.
//
// CASO DE USO
//   Aqui se modela la produccion de 2 plantas, 3 lineas y 4 trimestres.
//   Cualquier dato tabulado con tres criterios cae en esta forma.
// ===========================================================================

#include <iomanip>
#include <iostream>

int main() {
    const int PLANTAS = 2;
    const int LINEAS = 3;
    const int TRIMESTRES = 4;

    int produccion[PLANTAS][LINEAS][TRIMESTRES] = {
        // planta 0
        {{100, 110, 120, 130},
         {200, 210, 220, 230},
         {300, 310, 320, 330}},
        // planta 1
        {{400, 410, 420, 430},
         {500, 510, 520, 530},
         {600, 610, 620, 630}}};

    std::cout << "Tamaños\n"
              << "  sizeof(produccion)          = " << sizeof(produccion) << " bytes ("
              << PLANTAS * LINEAS * TRIMESTRES << " enteros)\n"
              << "  sizeof(produccion[0])       = " << sizeof(produccion[0])
              << " bytes (una planta: int[3][4])\n"
              << "  sizeof(produccion[0][0])    = " << sizeof(produccion[0][0])
              << " bytes (una linea: int[4])\n"
              << "  sizeof(produccion[0][0][0]) = " << sizeof(produccion[0][0][0])
              << " bytes (un dato)\n\n";

    std::cout << "Recorrido con tres bucles anidados\n";
    for (int p = 0; p < PLANTAS; ++p) {
        std::cout << "  Planta " << p << '\n';
        for (int l = 0; l < LINEAS; ++l) {
            std::cout << "    Linea " << l << ": ";
            for (int t = 0; t < TRIMESTRES; ++t) {
                std::cout << std::setw(5) << produccion[p][l][t];
            }
            std::cout << '\n';
        }
    }

    std::cout << "\nComprobacion de la formula i*D1*D2 + j*D2 + k\n";
    const int* base = &produccion[0][0][0];
    bool todo_correcto = true;
    for (int p = 0; p < PLANTAS; ++p) {
        for (int l = 0; l < LINEAS; ++l) {
            for (int t = 0; t < TRIMESTRES; ++t) {
                const int indice_lineal = p * LINEAS * TRIMESTRES + l * TRIMESTRES + t;
                if (produccion[p][l][t] != base[indice_lineal]) {
                    todo_correcto = false;
                }
            }
        }
    }
    std::cout << "  produccion[p][l][t] == base[p*" << LINEAS * TRIMESTRES << " + l*" << TRIMESTRES
              << " + t] para todos los elementos: " << (todo_correcto ? "SI" : "NO") << '\n';

    std::cout << "\nEjemplo concreto: produccion[1][2][3]\n"
              << "  indice lineal = 1*" << LINEAS * TRIMESTRES << " + 2*" << TRIMESTRES
              << " + 3 = " << (1 * LINEAS * TRIMESTRES + 2 * TRIMESTRES + 3) << '\n'
              << "  valor por indices = " << produccion[1][2][3] << '\n'
              << "  valor por formula = " << base[1 * LINEAS * TRIMESTRES + 2 * TRIMESTRES + 3]
              << '\n';

    // Agregaciones: es el uso real de estos arreglos.
    std::cout << "\nTotales por planta\n";
    for (int p = 0; p < PLANTAS; ++p) {
        long total = 0;
        for (int l = 0; l < LINEAS; ++l) {
            for (int t = 0; t < TRIMESTRES; ++t) {
                total += produccion[p][l][t];
            }
        }
        std::cout << "  planta " << p << ": " << total << '\n';
    }

    std::cout << "\nTotales por trimestre (todas las plantas y lineas)\n";
    for (int t = 0; t < TRIMESTRES; ++t) {
        long total = 0;
        for (int p = 0; p < PLANTAS; ++p) {
            for (int l = 0; l < LINEAS; ++l) {
                total += produccion[p][l][t];
            }
        }
        std::cout << "  trimestre " << t << ": " << total << '\n';
    }

    std::cout << "\nCOMO SE PASA A UNA FUNCION\n"
              << "  void f(int v[][3][4], int plantas);   // solo la 1a dimension se omite\n"
              << "  void f(int (*v)[3][4], int plantas);  // la firma real\n"
              << "  A partir de tres dimensiones, lo habitual en codigo profesional es\n"
              << "  usar un bloque lineal con la formula del indice, o std::mdspan (C++23).\n";
    return 0;
}
