// ===========================================================================
// 19 - Pasar una matriz a una funcion
// Bloque 10 (15 min) - Arreglos bidimensionales
//
// OBJETIVO
//   Ver por que al declarar el parametro se puede omitir el numero de filas
//   pero NUNCA el de columnas.
//
// REGLA
//   void f(int m[][4], int filas);   valido
//   void f(int m[3][4], int filas);  valido (el 3 se ignora)
//   void f(int m[][], int filas);    ERROR: falta el numero de columnas
//
// PARA LA EXPOSICION
//   La razon es la formula del ejemplo anterior: sin COLUMNAS, el compilador
//   no puede calcular donde empieza cada fila.
// ===========================================================================

#include <iostream>

const int COLUMNAS = 4;

void imprime(const int m[4][5], int filas) {
    for (int i = 0; i < filas; ++i) {
        std::cout << "  ";
        for (int j = 0; j < COLUMNAS; ++j) {
            std::cout << m[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

// Sin const: la funcion modifica la matriz del llamador.
void multiplica_por(int m[][COLUMNAS], int filas, int factor) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            m[i][j] = m[i][j] * factor;
        }
    }
}

int suma_total(const int m[][COLUMNAS], int filas) {
    int total = 0;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            total = total + m[i][j];
        }
    }
    return total;
}

int main() {
    const int FILAS = 3;
    int m[FILAS][COLUMNAS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };


    std::cout << "Matriz original:\n";
    imprime(m, FILAS);

    std::cout << "\nsuma_total = " << suma_total(m, FILAS) << "\n\n";

    multiplica_por(m, FILAS, 10);
    std::cout << "Despues de multiplica_por(m, 3, 10):\n";
    imprime(m, FILAS);

    std::cout << "\nCONCLUSION: igual que con los arreglos de una dimension,\n"
              << "a la funcion le llega la direccion: la matriz no se copia\n"
              << "y la funcion puede modificarla.\n";
    return 0;
}
