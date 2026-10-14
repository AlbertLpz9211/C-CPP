// ===========================================================================
// Soluciones de la Practica 3 - Arreglos y matrices
//
//   clang++ -std=c++20 -Wall -Wextra -Wpedantic solucion-practica-3.cpp -o p3
//
// El ejercicio 5 (medicion) conviene compilarlo con -O2:
//   clang++ -std=c++20 -O2 solucion-practica-3.cpp -o p3
// ===========================================================================

#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <span>
#include <vector>

// --- Ejercicio 1: tres correcciones de la funcion suma ---------------------
int suma_puntero(const int* v, std::size_t n) {  // 1) puntero + tamaño
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) {
        s += v[i];
    }
    return s;
}

template <std::size_t N>
int suma_referencia(const int (&v)[N]) {  // 2) referencia a arreglo, N deducido
    int s = 0;
    for (int x : v) {
        s += x;
    }
    return s;
}

int suma_span(std::span<const int> v) {  // 3) std::span (C++20)
    int s = 0;
    for (int x : v) {
        s += x;
    }
    return s;
}

// --- Ejercicio 3: suma por filas, en las dos formas ------------------------
// a) Parametro de salida: es lo unico posible con arreglos crudos, porque una
//    funcion no puede devolver un arreglo por valor.
void sumas_por_fila_salida(const double (&m)[3][4], double (&resultado)[3]) {
    for (std::size_t i = 0; i < 3; ++i) {
        resultado[i] = 0.0;
        for (std::size_t j = 0; j < 4; ++j) {
            resultado[i] += m[i][j];
        }
    }
}

// b) Valor de retorno con std::array: preferible segun F.20.
std::array<double, 3> sumas_por_fila(const double (&m)[3][4]) {
    std::array<double, 3> r{};
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 4; ++j) {
            r[i] += m[i][j];
        }
    }
    return r;
}

// --- Ejercicio 4: transpuesta generica ------------------------------------
template <std::size_t F, std::size_t C>
void transpuesta(const int (&a)[F][C], int (&r)[C][F]) {
    for (std::size_t i = 0; i < F; ++i) {
        for (std::size_t j = 0; j < C; ++j) {
            r[j][i] = a[i][j];
        }
    }
}

int main() {
    std::cout << "Ejercicio 1\n";
    int v[6] = {1, 2, 3, 4, 5, 6};
    std::cout << "   suma_puntero    = " << suma_puntero(v, std::size(v)) << '\n'
              << "   suma_referencia = " << suma_referencia(v) << '\n'
              << "   suma_span       = " << suma_span(v) << "\n\n";

    std::cout << "Ejercicio 2\n";
    int m[4][6] = {};
    std::cout << "   m[2] es de tipo int[6] (una fila)\n"
              << "   sizeof(m)      = " << sizeof(m) << " bytes\n"
              << "   indice lineal de m[2][3] = 2*6 + 3 = " << (2 * 6 + 3) << '\n';
    m[2][3] = 99;
    std::cout << "   *(&m[0][0] + 15) = " << *(&m[0][0] + 15) << " y *(m[2] + 3) = "
              << *(m[2] + 3) << "\n\n";

    std::cout << "Ejercicio 3\n";
    double tabla[3][4] = {{1, 2, 3, 4}, {10, 20, 30, 40}, {0.5, 0.5, 0.5, 0.5}};
    double salida[3] = {};
    sumas_por_fila_salida(tabla, salida);
    std::cout << "   parametro de salida: ";
    for (double s : salida) {
        std::cout << s << ' ';
    }
    auto devuelto = sumas_por_fila(tabla);
    std::cout << "\n   valor de retorno   : ";
    for (double s : devuelto) {
        std::cout << s << ' ';
    }
    std::cout << "\n\n";

    std::cout << "Ejercicio 4\n";
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int t[3][2] = {};
    transpuesta(a, t);
    for (const auto& fila : t) {
        std::cout << "   ";
        for (int x : fila) {
            std::cout << std::setw(4) << x;
        }
        std::cout << '\n';
    }
    // transpuesta(a, a);  // no compila: int[2][3] no es int[3][2]
    std::cout << "   (transpuesta(a, a) no compila: dimensiones incompatibles)\n\n";

    std::cout << "Ejercicio 5\n";
    const int N = 1000;
    std::vector<int> grande(static_cast<std::size_t>(N) * N, 1);
    auto idx = [](int i, int j) { return static_cast<std::size_t>(i) * N + j; };
    using reloj = std::chrono::steady_clock;

    auto t0 = reloj::now();
    long long por_filas = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            por_filas += grande[idx(i, j)];
        }
    }
    auto t1 = reloj::now();
    long long por_columnas = 0;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            por_columnas += grande[idx(i, j)];
        }
    }
    auto t2 = reloj::now();

    auto ms = [](auto d, auto h) {
        return std::chrono::duration<double, std::milli>(h - d).count();
    };
    std::cout << std::fixed << std::setprecision(2) << "   por filas    : " << ms(t0, t1)
              << " ms (suma " << por_filas << ")\n"
              << "   por columnas : " << ms(t1, t2) << " ms (suma " << por_columnas << ")\n"
              << "   Misma suma, distinto tiempo: el recorrido por filas aprovecha la\n"
              << "   linea de cache; el de columnas salta " << N * sizeof(int)
              << " bytes en cada acceso.\n";
    return 0;
}
