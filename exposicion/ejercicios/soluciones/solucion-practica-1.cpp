// ===========================================================================
// Soluciones de la Practica 1 - Paso de argumentos por valor
//
// Compilar (no forma parte de los objetivos de CMake, es material de apoyo):
//   clang++ -std=c++20 -Wall -Wextra -Wpedantic solucion-practica-1.cpp -o p1
// ===========================================================================

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// --- Ejercicio 1 -----------------------------------------------------------
// Intercambio aritmetico sobre COPIAS: funciona dentro, no fuera.
void misterio(int a, int b) {
    a = a + b;
    b = a - b;
    a = a - b;
    std::cout << "   dentro: a=" << a << " b=" << b << '\n';
}

// --- Ejercicio 2 -----------------------------------------------------------
void duplica_mal(int n) {
    n = n * 2;  // modifica la copia
}

void duplica_bien(int& n) {  // la correccion: referencia
    n = n * 2;
}

// --- Ejercicio 3 -----------------------------------------------------------
double area(double radio) {  // barato de copiar -> valor
    return 3.14159265358979 * radio * radio;
}

void imprime(const std::string& texto) {  // solo lee, caro de copiar -> const&
    std::cout << "   " << texto << '\n';
}

void a_mayusculas(std::string& texto) {  // lo modifica -> &
    for (char& c : texto) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
}

int cuenta_pares(const std::vector<int>& datos) {  // solo lee -> const&
    int total = 0;
    for (int v : datos) {
        if (v % 2 == 0) {
            ++total;
        }
    }
    return total;
}

void ordena(std::vector<int>& datos) {  // lo modifica -> &
    std::sort(datos.begin(), datos.end());
}

// --- Ejercicio 4 -----------------------------------------------------------
struct Dato {
    Dato() = default;
    Dato(const Dato&) {
        ++copias;
        std::cout << "   copia numero " << copias << '\n';
    }
    Dato& operator=(const Dato&) = delete;
    static int copias;
};
int Dato::copias = 0;

void por_valor(Dato d) {
    (void)d;
}

void por_referencia(const Dato& d) {
    (void)d;
}

int main() {
    std::cout << "Ejercicio 1\n";
    int x = 3;
    int y = 8;
    misterio(x, y);
    std::cout << "   fuera : x=" << x << " y=" << y << "  <-- sin cambios\n\n";

    std::cout << "Ejercicio 2\n";
    int valor = 21;
    duplica_mal(valor);
    std::cout << "   con duplica_mal : " << valor << '\n';
    duplica_bien(valor);
    std::cout << "   con duplica_bien: " << valor << "\n\n";

    std::cout << "Ejercicio 3\n";
    std::cout << "   area(2.0) = " << area(2.0) << '\n';
    std::string texto = "paso de argumentos";
    imprime(texto);
    a_mayusculas(texto);
    imprime(texto);
    std::vector<int> datos{5, 2, 9, 4, 7, 6};
    std::cout << "   pares = " << cuenta_pares(datos) << '\n';
    ordena(datos);
    std::cout << "   ordenado: ";
    for (int v : datos) {
        std::cout << v << ' ';
    }
    std::cout << "\n\n";

    std::cout << "Ejercicio 4 (se esperan 3 copias)\n";
    Dato d;
    por_valor(d);
    por_referencia(d);
    Dato otro = d;
    por_valor(otro);
    std::cout << "   total de copias: " << Dato::copias << '\n';
    return 0;
}
