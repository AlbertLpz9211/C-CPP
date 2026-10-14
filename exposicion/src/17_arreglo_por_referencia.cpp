// ===========================================================================
// 17 - Pasar un arreglo por referencia (sin perder el tamaño)
// Bloque 8 (20 min) - Arreglos como parametros
//
// OBJETIVO
//   Si el decaimiento borra el tamaño, la referencia a arreglo lo conserva.
//   La sintaxis asusta pero se lee con la misma regla de siempre:
//
//       void f(int (&v)[10]);
//              |    |    |
//              |    |    +-- de 10 elementos
//              |    +------- referencia a un arreglo
//              +------------ de int
//
//   Los parentesis son obligatorios: 'int& v[10]' significaria otra cosa
//   (un arreglo de referencias, que no existe en C++).
//
// VENTAJA   dentro de la funcion, sizeof(v) y std::size(v) funcionan.
// LIMITE    el tamaño forma parte del tipo: f solo acepta arreglos de 10.
//           La plantilla resuelve ese limite deduciendo N.
// ===========================================================================

#include <iostream>
#include <iterator>

// 1) Referencia a un arreglo de tamaño fijo. Solo acepta int[10].
void imprime_diez(const int (&v)[10]) {
    std::cout << "    sizeof(v) = " << sizeof(v) << " bytes, std::size(v) = " << std::size(v)
              << " elementos  <-- el tamaño sobrevivio\n      ";
    for (int x : v) {  // el for por rango funciona porque el tipo conserva N
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

// 2) Plantilla: N lo deduce el compilador en cada llamada.
//    Es la forma idiomatica anterior a std::span.
template <std::size_t N>
void imprime_cualquiera(const int (&v)[N]) {
    std::cout << "    N deducido = " << N << " -> ";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

// 3) Plantilla doblemente generica: tipo y tamaño.
template <typename T, std::size_t N>
T suma(const T (&v)[N]) {
    T total{};
    for (const T& x : v) {
        total += x;
    }
    return total;
}

// 4) Sin const, la funcion puede modificar el arreglo del llamador.
template <std::size_t N>
void duplica_todo(int (&v)[N]) {
    for (int& x : v) {
        x *= 2;
    }
}

int main() {
    int diez[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tres[3] = {100, 200, 300};
    double reales[4] = {1.5, 2.5, 3.5, 4.5};

    std::cout << "1) Referencia a arreglo de tamaño fijo\n";
    imprime_diez(diez);
    // imprime_diez(tres);  // error: no matching function; el tipo int[3] no es int[10]
    std::cout << "   (imprime_diez(tres) NO compila: el tamaño es parte del tipo)\n\n";

    std::cout << "2) Plantilla con N deducido\n";
    imprime_cualquiera(diez);
    imprime_cualquiera(tres);

    std::cout << "\n3) Plantilla generica en tipo y tamaño\n"
              << "   suma(diez)   = " << suma(diez) << '\n'
              << "   suma(tres)   = " << suma(tres) << '\n'
              << "   suma(reales) = " << suma(reales) << '\n';

    std::cout << "\n4) Sin const: modifica el arreglo del llamador\n   antes  : ";
    for (int x : tres) {
        std::cout << x << ' ';
    }
    duplica_todo(tres);
    std::cout << "\n   despues: ";
    for (int x : tres) {
        std::cout << x << ' ';
    }
    std::cout << "\n\nCUANDO USARLO\n"
              << "  Cuando el arreglo es crudo y quieres conservar el tamaño sin pasar\n"
              << "  un parametro extra. Si puedes usar C++20, std::span es mas simple\n"
              << "  y ademas acepta vector, array y arreglo crudo con la misma firma.\n";
    return 0;
}
