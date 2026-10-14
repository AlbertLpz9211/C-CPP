// ===========================================================================
// Soluciones de la Practica 2 - Referencias, punteros y const
//
//   clang++ -std=c++20 -Wall -Wextra -Wpedantic solucion-practica-2.cpp -o p2
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

// --- Ejercicio 1: las cuatro firmas ---------------------------------------
double promedio(const std::vector<double>& datos) {  // 1) solo lee, caro -> const&
    if (datos.empty()) {
        return 0.0;
    }
    double suma = 0.0;
    for (double v : datos) {
        suma += v;
    }
    return suma / static_cast<double>(datos.size());
}

void duplica(int& n) {  // 2) lo modifica -> &
    n *= 2;
}

void registra(const std::string* mensaje) {  // 3) opcional -> puntero
    if (mensaje == nullptr) {
        std::cout << "   (sin mensaje)\n";
        return;
    }
    std::cout << "   " << *mensaje << '\n';
}

struct Extremos {  // 4) dos salidas -> struct de retorno (F.21)
    double minimo;
    double maximo;
};

Extremos extremos(const std::vector<double>& datos) {
    Extremos r{datos.front(), datos.front()};
    for (double v : datos) {
        if (v < r.minimo) {
            r.minimo = v;
        }
        if (v > r.maximo) {
            r.maximo = v;
        }
    }
    return r;
}

// --- Ejercicio 2: errores de vida -----------------------------------------
// MAL: devuelve una referencia a una local. El compilador avisa.
//   const std::string& saluda(const std::string& nombre) {
//       std::string mensaje = "Hola, " + nombre;
//       return mensaje;
//   }
// BIEN: devolver por valor.
std::string saluda(const std::string& nombre) {
    return "Hola, " + nombre;
}

// Esta version SI es correcta: la referencia se toma despues del push_back.
int& primer_elemento(std::vector<int>& v) {
    v.push_back(0);
    return v[0];
}

// Esta seria INCORRECTA: la referencia se toma antes de que el vector crezca.
//   int& primer_elemento_mal(std::vector<int>& v) {
//       int& r = v[0];
//       v.push_back(0);   // puede realojar e invalidar r
//       return r;
//   }

// --- Ejercicio 4: pon a cero el mayor -------------------------------------
// Version con punteros: acepta nulos, hay que comprobarlos.
void cero_al_mayor(int* a, int* b) {
    if (a == nullptr && b == nullptr) {
        return;
    }
    if (a == nullptr) {
        *b = 0;
        return;
    }
    if (b == nullptr) {
        *a = 0;
        return;
    }
    if (*a >= *b) {
        *a = 0;
    } else {
        *b = 0;
    }
}

// Version con referencias: mas simple, pero exige que existan los dos.
void cero_al_mayor(int& a, int& b) {
    if (a >= b) {
        a = 0;
    } else {
        b = 0;
    }
}

int main() {
    std::cout << "Ejercicio 1\n";
    std::vector<double> datos{4.0, 9.5, 1.25, 7.0};
    std::cout << "   promedio = " << promedio(datos) << '\n';
    int n = 21;
    duplica(n);
    std::cout << "   duplica(21) -> " << n << '\n';
    std::string msg = "evento registrado";
    registra(&msg);
    registra(nullptr);
    auto [mn, mx] = extremos(datos);
    std::cout << "   minimo=" << mn << " maximo=" << mx << "\n\n";

    std::cout << "Ejercicio 2\n";
    std::cout << "   " << saluda("Alberto") << '\n';
    std::vector<int> v{10, 20, 30};
    int& primero = primer_elemento(v);
    std::cout << "   primer_elemento devolvio " << primero << " (valido: la referencia\n"
              << "   se tomo despues del push_back)\n\n";

    std::cout << "Ejercicio 3: ver la tabla del enunciado\n\n";

    std::cout << "Ejercicio 4\n";
    int a = 5;
    int b = 9;
    cero_al_mayor(&a, &b);
    std::cout << "   con punteros   : a=" << a << " b=" << b << '\n';
    a = 5;
    b = 9;
    cero_al_mayor(a, b);
    std::cout << "   con referencias: a=" << a << " b=" << b << '\n';
    a = 5;
    cero_al_mayor(&a, nullptr);
    std::cout << "   con un nulo    : a=" << a << "  (la version con referencias no\n"
              << "   puede expresar este caso; es el criterio F.60)\n";
    return 0;
}
