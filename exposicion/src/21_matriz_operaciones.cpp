// ===========================================================================
// 21 - Operaciones con matrices
// Bloque 9 (25 min) - Arreglos multidimensionales
//
// OBJETIVO
//   Los tres ejercicios que siempre aparecen en este tema: suma, transpuesta
//   y producto de matrices. Sirven para practicar el manejo de indices y para
//   ver cuando conviene pasar por referencia y cuando devolver por valor.
//
// DECISIONES DE DISEÑO QUE VALE LA PENA SEÑALAR
//   - Las matrices de entrada van por referencia a const: no se copian y no
//     se pueden modificar.
//   - La matriz de salida va por referencia sin const: es un parametro de
//     salida. Con arreglos crudos no hay alternativa, porque una funcion no
//     puede devolver un arreglo por valor. Con std::array si se podria.
//   - En el producto, el numero de columnas de A debe ser igual al numero de
//     filas de B. Aqui esa condicion la verifica el compilador, porque las
//     dimensiones forman parte del tipo.
// ===========================================================================

#include <iomanip>
#include <iostream>

template <std::size_t F, std::size_t C>
void imprime(const char* etiqueta, const int (&m)[F][C]) {
    std::cout << "  " << etiqueta << " (" << F << "x" << C << ")\n";
    for (std::size_t i = 0; i < F; ++i) {
        std::cout << "    ";
        for (std::size_t j = 0; j < C; ++j) {
            std::cout << std::setw(6) << m[i][j];
        }
        std::cout << '\n';
    }
}

// Suma elemento a elemento. Requiere dimensiones iguales; el tipo lo garantiza.
template <std::size_t F, std::size_t C>
void suma(const int (&a)[F][C], const int (&b)[F][C], int (&resultado)[F][C]) {
    for (std::size_t i = 0; i < F; ++i) {
        for (std::size_t j = 0; j < C; ++j) {
            resultado[i][j] = a[i][j] + b[i][j];
        }
    }
}

// Transpuesta: el resultado tiene las dimensiones intercambiadas.
template <std::size_t F, std::size_t C>
void transpuesta(const int (&a)[F][C], int (&resultado)[C][F]) {
    for (std::size_t i = 0; i < F; ++i) {
        for (std::size_t j = 0; j < C; ++j) {
            resultado[j][i] = a[i][j];
        }
    }
}

// Producto: (F x K) * (K x C) = (F x C). La K comun la impone la firma.
template <std::size_t F, std::size_t K, std::size_t C>
void producto(const int (&a)[F][K], const int (&b)[K][C], int (&resultado)[F][C]) {
    for (std::size_t i = 0; i < F; ++i) {
        for (std::size_t j = 0; j < C; ++j) {
            int acumulado = 0;
            for (std::size_t k = 0; k < K; ++k) {
                acumulado += a[i][k] * b[k][j];
            }
            resultado[i][j] = acumulado;
        }
    }
}

int main() {
    int a[2][3] = {{1, 2, 3},
                   {4, 5, 6}};
    int b[2][3] = {{10, 20, 30},
                   {40, 50, 60}};

    imprime("A", a);
    imprime("B", b);

    int s[2][3] = {};
    suma(a, b, s);
    std::cout << "\nSUMA A + B\n";
    imprime("S", s);

    int t[3][2] = {};
    transpuesta(a, t);
    std::cout << "\nTRANSPUESTA de A\n";
    imprime("A^T", t);

    // (2x3) * (3x2) = (2x2)
    int p[2][2] = {};
    producto(a, t, p);
    std::cout << "\nPRODUCTO A * A^T\n";
    imprime("P", p);

    std::cout << "\n  p[0][0] = fila 0 de A por columna 0 de A^T\n"
              << "          = 1*1 + 2*2 + 3*3 = " << p[0][0] << '\n';

    std::cout << "\nSEGURIDAD DE TIPOS\n"
              << "  suma(a, t, s);      // no compila: t es int[3][2], se esperaba int[2][3]\n"
              << "  producto(a, b, p);  // no compila: 3 columnas de A contra 2 filas de B\n"
              << "  Al llevar las dimensiones en el tipo, el compilador verifica la\n"
              << "  compatibilidad de las matrices. Con punteros crudos eso se pierde.\n";
    return 0;
}
