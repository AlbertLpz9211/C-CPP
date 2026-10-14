// ===========================================================================
// 23 - Por que el orden de los bucles cambia el rendimiento
// Bloque 9 (25 min) - Arreglos multidimensionales
//
// OBJETIVO
//   Demostrar de forma medible que "guardado por filas" no es un detalle
//   teorico. Recorrer una matriz por filas es varias veces mas rapido que
//   recorrerla por columnas, y el codigo es casi identico.
//
// EXPLICACION
//   La memoria se lee en bloques (lineas de cache, tipicamente 64 o 128 bytes).
//   Al leer m[i][0] el procesador trae de golpe los siguientes elementos de
//   esa fila, que estan contiguos. Si el bucle avanza por la fila, esos datos
//   ya estan cargados. Si avanza por columnas, cada acceso salta COLUMNAS*4
//   bytes y obliga a traer una linea nueva casi siempre.
//
// COMO EJECUTARLO
//   Los sanitizers distorsionan la medicion. Para este ejemplo conviene
//   compilar aparte, optimizado:
//       clang++ -std=c++20 -O2 23_orden_de_recorrido.cpp -o /tmp/recorrido
//       /tmp/recorrido
// ===========================================================================

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const int N = 2048;  // matriz N x N de int: 16 MiB con N=2048

    // Se reserva en el monton (heap): 16 MiB no caben en la pila.
    std::vector<int> m(static_cast<std::size_t>(N) * N, 1);

    auto indice = [](int i, int j) { return static_cast<std::size_t>(i) * N + j; };

    using reloj = std::chrono::steady_clock;

    // --- Recorrido por filas: j avanza sobre memoria contigua ---------------
    auto t0 = reloj::now();
    long long suma_filas = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            suma_filas += m[indice(i, j)];
        }
    }
    auto t1 = reloj::now();

    // --- Recorrido por columnas: cada paso salta N enteros ------------------
    long long suma_columnas = 0;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            suma_columnas += m[indice(i, j)];
        }
    }
    auto t2 = reloj::now();

    auto ms = [](auto desde, auto hasta) {
        return std::chrono::duration<double, std::milli>(hasta - desde).count();
    };

    const double t_filas = ms(t0, t1);
    const double t_columnas = ms(t1, t2);

    std::cout << std::fixed << std::setprecision(2)
              << "Matriz de " << N << " x " << N << " enteros ("
              << (static_cast<std::size_t>(N) * N * sizeof(int)) / (1024 * 1024) << " MiB)\n\n"
              << "  por filas    (i externo, j interno): " << std::setw(8) << t_filas
              << " ms   suma=" << suma_filas << '\n'
              << "  por columnas (j externo, i interno): " << std::setw(8) << t_columnas
              << " ms   suma=" << suma_columnas << "\n\n";

    if (t_filas > 0.0) {
        std::cout << "  El recorrido por columnas tardo " << (t_columnas / t_filas)
                  << " veces mas.\n\n";
    }

    std::cout << "LAS DOS SUMAS SON IGUALES: el resultado no cambia, solo el tiempo.\n"
              << "Cambiar el orden de dos bucles anidados es la optimizacion mas barata\n"
              << "que existe en computo con matrices.\n\n"
              << "REGLA: en C y C++, el ULTIMO indice debe ser el del bucle MAS INTERNO.\n";
    return 0;
}
