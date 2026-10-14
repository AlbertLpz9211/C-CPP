// ===========================================================================
// 10 - Devolver resultados: parametros de salida vs valor de retorno
// Bloque 4 (35 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   El paso por referencia permite que una funcion "devuelva" varios datos
//   escribiendo en parametros de salida. Es una tecnica clasica, heredada de
//   C, y sigue siendo util; pero C++ moderno prefiere el valor de retorno.
//
// GUIA
//   C++ Core Guidelines
//     F.20: "For 'out' output values, prefer return values to output parameters".
//     F.21: "To return multiple 'out' values, prefer returning a struct".
//   Razon: el valor de retorno no se puede ignorar por accidente, no obliga a
//   declarar variables sin inicializar antes de la llamada y se compone mejor.
// ===========================================================================

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

// --- Estilo 1: parametros de salida por referencia --------------------------
void estadisticas_por_parametro(const std::vector<double>& datos, double& minimo, double& maximo,
                                double& media) {
    minimo = datos.front();
    maximo = datos.front();
    double suma = 0.0;
    for (double v : datos) {
        if (v < minimo) {
            minimo = v;
        }
        if (v > maximo) {
            maximo = v;
        }
        suma += v;
    }
    media = suma / static_cast<double>(datos.size());
}

// --- Estilo 2: devolver una estructura (recomendado) ------------------------
struct Estadisticas {
    double minimo;
    double maximo;
    double media;
};

Estadisticas estadisticas(const std::vector<double>& datos) {
    Estadisticas r{datos.front(), datos.front(), 0.0};
    double suma = 0.0;
    for (double v : datos) {
        if (v < r.minimo) {
            r.minimo = v;
        }
        if (v > r.maximo) {
            r.maximo = v;
        }
        suma += v;
    }
    r.media = suma / static_cast<double>(datos.size());
    return r;
}

// --- Estilo 3: entrada/salida real (el parametro entra CON un valor y sale
// modificado). Aqui el paso por referencia sin const es la eleccion correcta.
void normaliza(std::vector<double>& datos) {
    double suma = 0.0;
    for (double v : datos) {
        suma += v * v;
    }
    const double norma = std::sqrt(suma);
    if (norma == 0.0) {
        return;
    }
    for (double& v : datos) {  // referencia en el for para poder escribir
        v /= norma;
    }
}

int main() {
    const std::vector<double> muestras{12.5, 7.0, 19.75, 3.25, 15.0};

    // Estilo 1: hay que declarar tres variables antes, sin valor util.
    double minimo = 0.0;
    double maximo = 0.0;
    double media = 0.0;
    estadisticas_por_parametro(muestras, minimo, maximo, media);
    std::cout << "Estilo 1 - parametros de salida\n"
              << "  minimo=" << minimo << " maximo=" << maximo << " media=" << media << '\n'
              << "  Inconveniente: al leer la llamada no se sabe cuales argumentos son\n"
              << "  de entrada y cuales de salida sin ir a ver la firma.\n\n";

    // Estilo 2: una sola expresion, con enlace estructurado (C++17).
    auto [mn, mx, md] = estadisticas(muestras);
    std::cout << "Estilo 2 - devolver una estructura (preferido)\n"
              << "  minimo=" << mn << " maximo=" << mx << " media=" << md << '\n'
              << "  Ventaja: 'auto [mn, mx, md] = estadisticas(muestras);' se lee sola.\n\n";

    // Estilo 3: entrada/salida genuina.
    std::vector<double> vector_a_normalizar{3.0, 4.0};
    normaliza(vector_a_normalizar);
    std::cout << "Estilo 3 - entrada/salida con T&\n  (3, 4) normalizado = (";
    std::cout << vector_a_normalizar[0] << ", " << vector_a_normalizar[1] << ")\n\n";

    std::cout << "CRITERIO\n"
              << "  Solo salida            -> valor de retorno (o struct si son varios)\n"
              << "  Entra y sale modificado-> T&\n"
              << "  Solo entra, es grande  -> const T&\n";
    return 0;
}
