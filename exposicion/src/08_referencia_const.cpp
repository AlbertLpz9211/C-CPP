// ===========================================================================
// 08 - Referencia a const: leer sin copiar
// Bloque 5 (20 min) - const, punteros vs referencias
//
// OBJETIVO
//   const T& es el parametro mas frecuente en C++ moderno. Combina lo mejor
//   de los dos mundos: no copia (barato) y no permite modificar (seguro).
//
// TRES PROPIEDADES QUE HAY QUE SABER
//   1. No copia el argumento.
//   2. El compilador impide modificarlo dentro de la funcion.
//   3. Acepta mas argumentos que T&: temporales, literales, resultados de
//      conversiones y objetos const. Un T& (no const) los rechaza.
//
// GUIA
//   C++ Core Guidelines F.16: parametros de entrada; F.17: parametros de
//   entrada/salida por T&. La eleccion de const documenta la intencion.
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>

// Parametro de entrada: no se copia y no se modifica.
std::size_t longitud(const std::string& texto) {
    // texto[0] = 'X';  // error: cannot assign to variable 'texto' with const-qualified type
    return texto.size();
}

// Parametro de entrada/salida: se modifica, por eso NO lleva const.
void agrega_saludo(std::string& texto) {
    texto = "Hola, " + texto;
}

double promedio(const std::vector<double>& muestras) {
    if (muestras.empty()) {
        return 0.0;
    }
    double suma = 0.0;
    for (double m : muestras) {
        suma += m;
    }
    return suma / static_cast<double>(muestras.size());
}

int main() {
    std::string nombre = "Alberto";

    std::cout << "1) const std::string& no copia y no modifica\n"
              << "   longitud(nombre) = " << longitud(nombre) << '\n'
              << "   nombre sigue siendo '" << nombre << "'\n\n";

    std::cout << "2) std::string& (sin const) si modifica\n"
              << "   antes   : " << nombre << '\n';
    agrega_saludo(nombre);
    std::cout << "   despues : " << nombre << "\n\n";

    std::cout << "3) const T& acepta argumentos que T& rechaza\n";
    std::cout << "   longitud(\"literal\")            = " << longitud("literal") << '\n';
    std::cout << "   longitud(std::string{\"temp\"})   = " << longitud(std::string{"temp"}) << '\n';
    const std::string fijo = "constante";
    std::cout << "   longitud(fijo)  [objeto const] = " << longitud(fijo) << "\n\n";

    // Estas NO compilan, porque un T& no const no se puede ligar a un temporal
    // ni a un objeto const:
    //   agrega_saludo("literal");   // error: no matching function ... candidate function
    //                               //        not viable: expects an lvalue
    //   agrega_saludo(fijo);        // error: binding value of type 'const std::string' to
    //                               //        reference to type 'std::string' drops qualifiers
    std::cout << "   (ver en el codigo las dos llamadas comentadas que NO compilan)\n\n";

    // 4) Un const T& puede ligarse a un temporal y le extiende la vida
    //    mientras la referencia siga viva. Esto es seguro y es lo que permite
    //    llamar promedio({1, 2, 3}) sin nombrar el vector.
    const std::vector<double>& lecturas = std::vector<double>{20.5, 21.0, 19.5, 22.25};
    std::cout << "4) vida extendida de un temporal ligado a const&\n"
              << "   promedio = " << promedio(lecturas) << '\n'
              << "   promedio({30, 40}) = " << promedio({30.0, 40.0}) << "\n\n";

    std::cout << "REGLA PRACTICA\n"
              << "  Entrada barata de copiar  -> por valor        (int, double, char)\n"
              << "  Entrada cara de copiar    -> const T&         (string, vector, clases)\n"
              << "  Entrada y salida          -> T&               (se documenta al modificar)\n";
    return 0;
}
