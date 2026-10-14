// ===========================================================================
// 24 - Que usar en lugar del arreglo crudo
// Bloque 10 (10 min) - Cierre
//
// OBJETIVO
//   El arreglo crudo hay que saberlo leer: aparece en C, en codigo heredado,
//   en sistemas embebidos y en las entrevistas de trabajo. Pero para escribir
//   codigo nuevo en C++ casi siempre hay una opcion mejor.
//
//   std::array<T,N>   tamaño fijo conocido en compilacion. Mismo rendimiento
//                     que el arreglo crudo, pero NO decae, conoce su tamaño,
//                     se copia, se asigna, se devuelve y tiene .at().
//
//   std::vector<T>    tamaño decidido en ejecucion y modificable. Es la
//                     respuesta correcta cuando el usuario decide cuantos
//                     elementos hay. Reserva la memoria en el monton.
//
//   std::span<T>      vista (direccion + tamaño) para PARAMETROS. No es dueña.
//
// PARA MATRICES
//   a) std::array<std::array<T,C>,F>  -> contigua, tamaño fijo, sintaxis [i][j]
//   b) std::vector<T> aplanado + indice i*C+j -> contiguo y dimensionable
//   c) std::vector<std::vector<T>>    -> comodo, pero NO contiguo: cada fila
//      es un bloque independiente. Es la opcion mas lenta de las tres.
//   d) std::mdspan (C++23)            -> vista multidimensional sobre (b)
// ===========================================================================

#include <array>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

// Una sola firma para arreglo crudo, array y vector.
double media(std::span<const double> datos) {
    if (datos.empty()) {
        return 0.0;
    }
    return std::accumulate(datos.begin(), datos.end(), 0.0) / static_cast<double>(datos.size());
}

// std::array SI se puede devolver por valor. Un arreglo crudo no.
std::array<int, 5> primeros_cinco_cuadrados() {
    std::array<int, 5> r{};
    for (std::size_t i = 0; i < r.size(); ++i) {
        r[i] = static_cast<int>((i + 1) * (i + 1));
    }
    return r;
}

// Matriz aplanada: un solo bloque contiguo y el indice calculado a mano.
class Matriz {
public:
    Matriz(std::size_t filas, std::size_t columnas)
        : filas_(filas), columnas_(columnas), datos_(filas * columnas, 0.0) {}

    double& operator()(std::size_t i, std::size_t j) {
        return datos_[i * columnas_ + j];
    }

    double operator()(std::size_t i, std::size_t j) const {
        return datos_[i * columnas_ + j];
    }

    std::size_t filas() const {
        return filas_;
    }

    std::size_t columnas() const {
        return columnas_;
    }

private:
    std::size_t filas_;
    std::size_t columnas_;
    std::vector<double> datos_;  // contiguo, como el arreglo crudo
};

int main() {
    std::cout << "1) std::array: el arreglo crudo, pero con modales\n";
    std::array<double, 4> a{1.0, 2.0, 3.0, 4.0};
    std::cout << "   a.size() = " << a.size() << ", a.at(2) = " << a.at(2)
              << ", sizeof(a) = " << sizeof(a) << " bytes (sin sobrecosto)\n";

    std::array<double, 4> copia = a;  // un arreglo crudo NO se puede asignar asi
    copia[0] = 99.0;
    std::cout << "   se copia y se asigna: copia[0]=" << copia[0] << ", a[0]=" << a[0] << '\n';

    auto cuadrados = primeros_cinco_cuadrados();  // devuelto por valor
    std::cout << "   devuelto por valor: ";
    for (int v : cuadrados) {
        std::cout << v << ' ';
    }
    std::cout << "\n\n";

    std::cout << "2) std::vector: tamaño decidido en ejecucion\n";
    std::size_t n = 6;  // podria venir de std::cin
    std::vector<double> v(n, 2.5);
    v.push_back(10.0);
    std::cout << "   size=" << v.size() << " capacity=" << v.capacity()
              << "  (crece solo; el arreglo crudo no puede)\n\n";

    std::cout << "3) std::span: una firma para los tres\n";
    double crudo[3] = {7.0, 8.0, 9.0};
    std::cout << "   media(crudo) = " << media(crudo) << '\n'
              << "   media(a)     = " << media(a) << '\n'
              << "   media(v)     = " << media(v) << "\n\n";

    std::cout << "4) Matriz aplanada sobre std::vector\n";
    Matriz m(3, 4);
    for (std::size_t i = 0; i < m.filas(); ++i) {
        for (std::size_t j = 0; j < m.columnas(); ++j) {
            m(i, j) = static_cast<double>(i * 10 + j);
        }
    }
    for (std::size_t i = 0; i < m.filas(); ++i) {
        std::cout << "   ";
        for (std::size_t j = 0; j < m.columnas(); ++j) {
            std::cout << std::setw(6) << m(i, j);
        }
        std::cout << '\n';
    }
    std::cout << "   Ventajas: dimensiones en ejecucion, memoria contigua, sintaxis m(i,j),\n"
              << "   y las dimensiones viajan con el objeto.\n\n";

    std::cout << "5) std::array de std::array: matriz de tamaño fijo con [i][j]\n";
    std::array<std::array<int, 3>, 2> tabla{{{1, 2, 3}, {4, 5, 6}}};
    for (const auto& fila : tabla) {
        std::cout << "   ";
        for (int x : fila) {
            std::cout << std::setw(4) << x;
        }
        std::cout << '\n';
    }

    std::cout << "\nCRITERIO FINAL\n"
              << "  Tamaño fijo y conocido al compilar -> std::array\n"
              << "  Tamaño decidido al ejecutar        -> std::vector\n"
              << "  Parametro de funcion               -> std::span (o const T&)\n"
              << "  Arreglo crudo                      -> para leer codigo ajeno y para C\n";
    return 0;
}
