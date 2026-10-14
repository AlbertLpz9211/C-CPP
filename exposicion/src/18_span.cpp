// ===========================================================================
// 18 - std::span: la respuesta moderna al decaimiento
// Bloque 8 (20 min) - Arreglos como parametros
//
// OBJETIVO
//   std::span<T> (C++20, cabecera <span>) es un objeto ligero que guarda
//   DIRECCION + TAMAÑO. No es dueño de la memoria: es una "vista" sobre una
//   secuencia contigua que ya existe.
//
// POR QUE IMPORTA
//   Una sola firma sirve para arreglo crudo, std::array y std::vector, y el
//   tamaño viaja junto con los datos, asi que ya no se pueden desincronizar.
//
//   C++ Core Guidelines
//     I.13: "Do not pass an array as a single pointer".
//     F.24: "Use a span<T> or a span_p<T> to designate a half-open sequence".
//
// COSTO
//   Un span son dos palabras (puntero y tamaño): 16 bytes en 64 bits. Se pasa
//   por VALOR, igual que un puntero. No copia los elementos.
//
// CUIDADO
//   Como no es dueño de nada, vale lo mismo que para las referencias: si el
//   contenedor original muere o se realoja, el span queda colgante.
// ===========================================================================

#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <string_view>
#include <vector>

// Una sola funcion para todos los contenedores contiguos.
double media(std::span<const double> datos) {
    if (datos.empty()) {
        return 0.0;
    }
    double suma = 0.0;
    for (double v : datos) {  // el for por rango funciona: span tiene begin/end
        suma += v;
    }
    return suma / static_cast<double>(datos.size());
}

// Sin const, el span permite escribir en los datos originales.
void escala(std::span<double> datos, double factor) {
    for (double& v : datos) {
        v *= factor;
    }
}

void imprime(std::string_view etiqueta, std::span<const double> datos) {
    std::cout << "  " << etiqueta << " (size=" << datos.size() << "): ";
    for (double v : datos) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}

int main() {
    double crudo[4] = {1.0, 2.0, 3.0, 4.0};
    std::array<double, 3> arreglo{10.0, 20.0, 30.0};
    std::vector<double> vector{5.0, 5.0, 5.0, 5.0, 5.0};

    std::cout << "Una misma funcion recibe los tres contenedores\n"
              << "  media(crudo)   = " << media(crudo) << '\n'
              << "  media(arreglo) = " << media(arreglo) << '\n'
              << "  media(vector)  = " << media(vector) << "\n\n";

    std::cout << "sizeof(std::span<const double>) = " << sizeof(std::span<const double>)
              << " bytes (puntero + tamaño)\n\n";

    std::cout << "Escritura a traves del span (sin const)\n";
    imprime("antes  ", crudo);
    escala(crudo, 10.0);
    imprime("despues", crudo);

    std::cout << "\nSubvistas sin copiar nada\n";
    std::span<const double> todo{vector};
    imprime("todo       ", todo);
    imprime("first(2)   ", todo.first(2));
    imprime("last(2)    ", todo.last(2));
    imprime("subspan(1,3)", todo.subspan(1, 3));

    std::cout << "\nCOMPARACION DE FIRMAS\n"
              << "  clasica : double media(const double* datos, std::size_t n);\n"
              << "            -> el llamador puede equivocarse al pasar n\n"
              << "  moderna : double media(std::span<const double> datos);\n"
              << "            -> imposible desincronizar datos y tamaño\n";
    return 0;
}
