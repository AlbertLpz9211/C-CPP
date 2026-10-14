// ===========================================================================
// 16 - Un arreglo no comprueba sus limites  (FALLA A PROPOSITO)
// Bloque 8 (25 min) - Arreglos unidimensionales
//
// OBJETIVO
//   Mostrar el error mas frecuente del tema: salirse del arreglo por uno.
//   El programa compila, se ejecuta y puede parecer correcto.
//
// REGLA
//   En un arreglo de N elementos, los indices validos van de 0 a N-1.
//   La condicion del bucle usa <, nunca <=.
//
// COMO EJECUTARLO (las dos formas, en este orden)
//   1) Compilado a mano, SIN comprobaciones:
//        clang++ -std=c++17 src/16_fuera_de_rango.cpp -o /tmp/fuera
//        /tmp/fuera                      -> termina sin quejarse de nada
//   2) Compilado por CMake en Debug, CON AddressSanitizer:
//        ./build/bin/bas_16_fuera_de_rango   -> se detiene y senala la linea
//
// PARA LA EXPOSICION
//   Ejecutarlo de las dos formas. El mismo programa se comporta distinto:
//   eso es exactamente lo que significa "comportamiento indefinido".
// ===========================================================================

#include <iostream>

int main(int argc, char* argv[]) {
    (void)argv;

    int antes = 1111;
    int v[5] = {10, 20, 30, 40, 50};
    int despues = 2222;

    std::cout << "El arreglo v tiene 5 elementos: indices validos 0..4\n\n";

    std::cout << "Recorrido CORRECTO (i < 5):\n  ";
    for (int i = 0; i < 5; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "Recorrido INCORRECTO (i <= 5): lee una posicion de mas\n  ";
    for (int i = 0; i <= 5; ++i) {
        // En i == 5 se lee memoria que no pertenece al arreglo.
        std::cout << v[i] << ' ';
    }
    std::cout << "\n\nEse ultimo numero no es de v. Es lo que hubiera al lado.\n\n";

    // El indice se calcula en tiempo de ejecucion (a partir de argc) para que
    // el compilador no pueda avisar: solo detecta los indices constantes.
    int fuera = 5 + argc - 1;

    std::cout << "Variables vecinas antes de escribir: antes = " << antes
              << ", despues = " << despues << '\n';

    v[fuera] = 7777;  // ESCRIBE fuera del arreglo

    std::cout << "Variables vecinas despues de escribir: antes = " << antes
              << ", despues = " << despues << '\n';
    std::cout << "Alguna pudo cambiar de valor sin que nadie la tocara.\n\n";

    std::cout << "CONCLUSION: comprobar los limites es trabajo del programador.\n"
              << "El compilador no lo hace y el programa no avisa.\n";
    return 0;
}
