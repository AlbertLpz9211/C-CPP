// ===========================================================================
// 05 - Cuando el paso por valor es la opcion correcta
// Bloque 2 (30 min) - Paso de argumentos por valor
//
// OBJETIVO
//   Evitar la conclusion equivocada "pasar por valor es malo". El paso por
//   valor es la opcion correcta en tres situaciones muy frecuentes.
//
//   1. Tipos baratos de copiar: int, double, char, bool, punteros, enum.
//      Pasar un int por referencia suele ser mas lento que copiarlo: la
//      referencia se implementa como una direccion (8 bytes) y ademas obliga
//      a un acceso indirecto a memoria.
//
//   2. Cuando la funcion necesita su propia copia de trabajo. Si de todos
//      modos vas a copiar dentro, pide la copia en el parametro: es mas claro
//      y permite al compilador evitar copias (copy elision).
//
//   3. Cuando la funcion se queda con el dato (sink). Parametro por valor
//      + std::move: un argumento temporal se mueve en vez de copiarse.
// ===========================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Caso 1: tipos baratos. Pasar por valor es lo idiomatico.
double area_rectangulo(double base, double altura) {
    return base * altura;
}

// Caso 2: la funcion necesita una copia para trabajar sin alterar el original.
// Pedirla en el parametro evita escribir la copia a mano dentro del cuerpo.
std::vector<int> ordenado(std::vector<int> copia) {
    std::sort(copia.begin(), copia.end());
    return copia;  // se mueve al retornar, no se copia
}

// Caso 3: sumidero. La clase se queda con el string.
class Usuario {
public:
    // Parametro por valor + move: un temporal se mueve, un lvalue se copia una vez.
    explicit Usuario(std::string nombre) : nombre_(std::move(nombre)) {}

    const std::string& nombre() const {
        return nombre_;
    }

private:
    std::string nombre_;
};

int main() {
    std::cout << "Caso 1 - tipos baratos de copiar\n"
              << "  area(3, 4) = " << area_rectangulo(3.0, 4.0) << '\n'
              << "  sizeof(double) = " << sizeof(double) << " bytes; una referencia ocupa "
              << sizeof(double*) << " bytes y anade una indireccion.\n\n";

    std::vector<int> original{5, 3, 9, 1, 7};
    std::vector<int> resultado = ordenado(original);

    std::cout << "Caso 2 - copia de trabajo explicita\n  original : ";
    for (int v : original) {
        std::cout << v << ' ';
    }
    std::cout << "\n  ordenado : ";
    for (int v : resultado) {
        std::cout << v << ' ';
    }
    std::cout << "\n  El original queda intacto porque la funcion recibio su propia copia.\n\n";

    Usuario u1{"Alberto"};                    // temporal -> se mueve al miembro
    std::string nombre_existente = "Yuridia";
    Usuario u2{nombre_existente};             // lvalue -> una copia, inevitable

    std::cout << "Caso 3 - parametro sumidero\n"
              << "  u1 = " << u1.nombre() << '\n'
              << "  u2 = " << u2.nombre() << " (nombre_existente sigue siendo '"
              << nombre_existente << "')\n\n"
              << "REGLA (Core Guidelines F.16): parametros de entrada baratos de copiar,\n"
              << "por valor; el resto, por referencia a const.\n";
    return 0;
}
