// ===========================================================================
// 19 - Arreglos multidimensionales: una matriz es un arreglo de arreglos
// Bloque 9 (25 min) - Arreglos multidimensionales
//
// OBJETIVO
//   Entender que 'int m[3][4]' NO es una tabla magica: es un arreglo de 3
//   elementos, y cada elemento es a su vez un arreglo de 4 int. De ahi salen
//   todas las reglas del tema.
//
// NORMA ([dcl.array]/9)
//   "Cuando varias especificaciones 'array of' son adyacentes se crea un tipo
//   de arreglo multidimensional". El ejemplo de la norma explica que en
//   x3d[i][j][k] el indice i se multiplica por el tamaño del objeto completo
//   de las dimensiones restantes.
//
// ORDEN DE FILAS (row-major)
//   C y C++ guardan la matriz FILA POR FILA, en un unico bloque contiguo:
//
//       m[3][4] en memoria:
//       [ m00 m01 m02 m03 | m10 m11 m12 m13 | m20 m21 m22 m23 ]
//         ---- fila 0 ----   ---- fila 1 ----   ---- fila 2 ----
//
//   La direccion de m[i][j] es:  base + (i * COLUMNAS + j) * sizeof(T)
//   (Fortran, MATLAB y Julia usan el orden inverso, columna por columna.
//    Es la causa de errores tipicos al portar codigo numerico.)
// ===========================================================================

#include <iomanip>
#include <iostream>

int main() {
    const int FILAS = 3;
    const int COLUMNAS = 4;

    // Inicializacion por filas: las llaves internas son las filas.
    int m[FILAS][COLUMNAS] = {{1, 2, 3, 4},
                              {5, 6, 7, 8},
                              {9, 10, 11, 12}};

    // Tambien es valido (menos legible): int m[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    // Y lo que falte se completa con ceros: int c[2][3] = {{1}, {4, 5}};

    std::cout << "Recorrido con dos bucles anidados\n";
    for (int i = 0; i < FILAS; ++i) {
        std::cout << "  fila " << i << ": ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << std::setw(3) << m[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nTamaños\n"
              << "  sizeof(m)       = " << sizeof(m) << " bytes  (toda la matriz)\n"
              << "  sizeof(m[0])    = " << sizeof(m[0]) << " bytes  (una fila: int[4])\n"
              << "  sizeof(m[0][0]) = " << sizeof(m[0][0]) << " bytes  (un elemento)\n"
              << "  filas    = sizeof(m)/sizeof(m[0])       = " << sizeof(m) / sizeof(m[0]) << '\n'
              << "  columnas = sizeof(m[0])/sizeof(m[0][0]) = " << sizeof(m[0]) / sizeof(m[0][0])
              << '\n';

    std::cout << "\nLa memoria es un unico bloque contiguo, fila por fila\n";
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            const auto desplazamiento =
                reinterpret_cast<const char*>(&m[i][j]) - reinterpret_cast<const char*>(&m[0][0]);
            std::cout << "  m[" << i << "][" << j << "] = " << std::setw(3) << m[i][j]
                      << "  direccion " << &m[i][j] << "  desplazamiento " << std::setw(3)
                      << desplazamiento << " bytes  = (" << i << "*" << COLUMNAS << "+" << j
                      << ")*" << sizeof(int) << '\n';
        }
    }

    std::cout << "\nComprobacion de la formula base + (i*COLUMNAS + j)\n";
    const int* base = &m[0][0];
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            const int por_indices = m[i][j];
            const int por_formula = base[i * COLUMNAS + j];
            if (por_indices != por_formula) {
                std::cout << "  DISCREPANCIA\n";
            }
        }
    }
    std::cout << "  m[i][j] == base[i*COLUMNAS + j] para todos los elementos.\n";

    std::cout << "\nm[0] es una FILA, y decae a puntero como cualquier arreglo\n"
              << "  m[1][2]   = " << m[1][2] << '\n'
              << "  *(m[1]+2) = " << *(m[1] + 2) << '\n'
              << "  Las dos expresiones son equivalentes por definicion del operador [].\n";

    std::cout << "\nfor por rango: la variable externa debe ser referencia a fila\n";
    for (const auto& fila : m) {  // fila es 'const int (&)[4]'
        for (int valor : fila) {
            std::cout << std::setw(3) << valor;
        }
        std::cout << '\n';
    }
    return 0;
}
