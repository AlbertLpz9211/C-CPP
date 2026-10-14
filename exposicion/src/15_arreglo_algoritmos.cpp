// ===========================================================================
// 15 - Algoritmos basicos sobre un arreglo
// Bloque 7 (25 min) - Arreglos unidimensionales
//
// OBJETIVO
//   Practicar el patron de recorrido con un caso realista: calificaciones de
//   un grupo. Estos cuatro algoritmos (acumular, buscar el extremo, buscar un
//   valor, ordenar) cubren la mayoria de los ejercicios del tema.
//
// PATRON COMUN
//   Todo recorrido de arreglo tiene la misma forma:
//       for (std::size_t i = 0; i < n; ++i) { ... v[i] ... }
//   El error tipico esta en la condicion: debe ser '<', nunca '<='.
// ===========================================================================

#include <algorithm>  // std::sort, std::max_element, std::find
#include <iomanip>
#include <iostream>
#include <iterator>

// Los parametros reciben puntero + tamaño porque el arreglo decae al pasarlo.
// El tema se explica en 16_decaimiento.cpp.
double media(const double* v, std::size_t n) {
    if (n == 0) {
        return 0.0;
    }
    double suma = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        suma += v[i];
    }
    return suma / static_cast<double>(n);
}

std::size_t indice_del_maximo(const double* v, std::size_t n) {
    std::size_t mejor = 0;
    for (std::size_t i = 1; i < n; ++i) {
        if (v[i] > v[mejor]) {
            mejor = i;
        }
    }
    return mejor;
}

// Busqueda lineal: devuelve el indice, o n si no lo encuentra.
std::size_t busca(const double* v, std::size_t n, double objetivo) {
    for (std::size_t i = 0; i < n; ++i) {
        if (v[i] == objetivo) {
            return i;
        }
    }
    return n;  // convencion: "una posicion mas alla del final" significa no encontrado
}

// Ordenamiento por burbuja: lento, pero es el que se pide en clase.
// Recibe el arreglo por puntero SIN const porque lo va a modificar.
void ordena_burbuja(double* v, std::size_t n) {
    for (std::size_t pasada = 0; pasada + 1 < n; ++pasada) {
        bool hubo_cambio = false;
        for (std::size_t i = 0; i + 1 < n - pasada; ++i) {
            if (v[i] > v[i + 1]) {
                std::swap(v[i], v[i + 1]);  // intercambio por referencia
                hubo_cambio = true;
            }
        }
        if (!hubo_cambio) {  // ya estaba ordenado
            break;
        }
    }
}

void imprime(const char* etiqueta, const double* v, std::size_t n) {
    std::cout << "  " << std::left << std::setw(12) << etiqueta << ": ";
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << std::fixed << std::setprecision(1) << v[i] << "  ";
    }
    std::cout << '\n';
}

int main() {
    double calificaciones[] = {87.5, 92.0, 78.25, 95.5, 60.0, 88.75, 71.5};
    const std::size_t n = std::size(calificaciones);

    std::cout << "Grupo de " << n << " estudiantes\n";
    imprime("originales", calificaciones, n);

    std::cout << "\nCalculos\n"
              << "  media                = " << media(calificaciones, n) << '\n';

    const std::size_t mejor = indice_del_maximo(calificaciones, n);
    std::cout << "  maxima               = " << calificaciones[mejor] << " (posicion " << mejor
              << ")\n";

    const double objetivo = 95.5;
    const std::size_t encontrado = busca(calificaciones, n, objetivo);
    std::cout << "  busqueda de " << objetivo << "     = ";
    if (encontrado == n) {
        std::cout << "no esta\n";
    } else {
        std::cout << "posicion " << encontrado << '\n';
    }

    std::cout << "\nOrdenamiento\n";
    ordena_burbuja(calificaciones, n);
    imprime("ordenadas", calificaciones, n);

    std::cout << "\nLo mismo con la biblioteca estandar (<algorithm>)\n"
              << "  std::sort(std::begin(v), std::end(v));\n"
              << "  std::max_element / std::find / std::accumulate\n";

    double otra_copia[] = {5.0, 1.0, 4.0, 2.0, 3.0};
    std::sort(std::begin(otra_copia), std::end(otra_copia));
    imprime("con sort", otra_copia, std::size(otra_copia));

    const double* maximo = std::max_element(std::begin(otra_copia), std::end(otra_copia));
    std::cout << "  max_element -> " << *maximo << "  (posicion "
              << (maximo - std::begin(otra_copia)) << ")\n";
    return 0;
}
