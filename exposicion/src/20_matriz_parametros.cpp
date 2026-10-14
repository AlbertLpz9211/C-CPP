// ===========================================================================
// 20 - Pasar una matriz a una funcion
// Bloque 9 (25 min) - Arreglos multidimensionales
//
// OBJETIVO
//   Aplicar la regla del decaimiento a dos dimensiones. Es donde mas se
//   equivoca la gente, y la razon es una sola:
//
//   int m[3][4] decae a 'puntero a arreglo de 4 int', es decir int (*)[4].
//   NO decae a int**. Un int** es otra cosa (arreglo de punteros) y no es
//   compatible con una matriz.
//
//   Por eso el compilador necesita conocer TODAS las dimensiones menos la
//   primera: sin el numero de columnas no puede calcular i*COLUMNAS + j.
//
//       void f(int m[][4], int filas);   // ok, la 1a dimension puede omitirse
//       void f(int m[3][4], int filas);  // el 3 se ignora
//       void f(int (*m)[4], int filas);  // la firma real de las dos anteriores
//       void f(int** m, ...);            // ERROR conceptual: NO es una matriz
// ===========================================================================

#include <iomanip>
#include <iostream>

const int COLUMNAS = 4;

// 1) Forma clasica: las columnas fijas en el tipo, las filas como parametro.
void imprime_clasica(const int m[][COLUMNAS], int filas) {
    for (int i = 0; i < filas; ++i) {
        std::cout << "    ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << std::setw(4) << m[i][j];
        }
        std::cout << '\n';
    }
}

// 2) Exactamente la misma funcion, escrita como lo que realmente es.
void imprime_puntero_a_fila(const int (*m)[COLUMNAS], int filas) {
    for (int i = 0; i < filas; ++i) {
        std::cout << "    ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << std::setw(4) << m[i][j];
        }
        std::cout << '\n';
    }
}

// 3) Referencia a la matriz completa: conserva las dos dimensiones.
template <std::size_t F, std::size_t C>
void imprime_por_referencia(const int (&m)[F][C]) {
    std::cout << "    (F=" << F << ", C=" << C << " deducidas por el compilador)\n";
    for (const auto& fila : m) {
        std::cout << "    ";
        for (int valor : fila) {
            std::cout << std::setw(4) << valor;
        }
        std::cout << '\n';
    }
}

// 4) Vista aplanada: se trata la matriz como un bloque lineal y se calcula el
//    indice a mano. Es lo que hacen por dentro las bibliotecas numericas.
void imprime_aplanada(const int* datos, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        std::cout << "    ";
        for (int j = 0; j < columnas; ++j) {
            std::cout << std::setw(4) << datos[i * columnas + j];
        }
        std::cout << '\n';
    }
}

// 5) Sin const: modifica la matriz del llamador (no hubo copia).
void multiplica_por(int m[][COLUMNAS], int filas, int factor) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            m[i][j] *= factor;
        }
    }
}

int main() {
    int m[3][COLUMNAS] = {{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12}};

    std::cout << "1) void f(const int m[][4], int filas)\n";
    imprime_clasica(m, 3);

    std::cout << "\n2) void f(const int (*m)[4], int filas)   [la misma funcion]\n";
    imprime_puntero_a_fila(m, 3);

    std::cout << "\n3) template<F,C> void f(const int (&m)[F][C])\n";
    imprime_por_referencia(m);

    std::cout << "\n4) void f(const int* datos, int filas, int columnas)  [vista aplanada]\n";
    imprime_aplanada(&m[0][0], 3, COLUMNAS);

    std::cout << "\n5) Sin const, la funcion modifica la matriz original\n";
    multiplica_por(m, 3, 10);
    imprime_clasica(m, 3);

    std::cout << "\nPOR QUE NO int**\n"
              << "  int** significa 'puntero a puntero a int': supone que en memoria hay\n"
              << "  un arreglo de DIRECCIONES, cada una apuntando a una fila suelta.\n"
              << "  Una matriz int[3][4] es un unico bloque de 12 enteros, sin ninguna\n"
              << "  tabla de direcciones. Por eso el compilador rechaza la conversion:\n"
              << "      cannot initialize a parameter of type 'int **' with an lvalue of\n"
              << "      type 'int[3][4]'\n";
    return 0;
}
