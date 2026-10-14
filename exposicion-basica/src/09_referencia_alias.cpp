// ===========================================================================
// 09 - La referencia es otro nombre para la misma variable
// Bloque 5 (30 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Ver que una referencia NO es una variable nueva: comparte direccion con
//   la variable original.
//
// REGLA
//   int& alias = valor;  crea un segundo nombre para 'valor'.
//   Debe inicializarse al declararse y no puede pasar a nombrar otra cosa.
//
// PARA LA EXPOSICION
//   Descomentar la declaracion sin inicializar para mostrar el error:
//   "declaration of reference variable requires an initializer".
// ===========================================================================

#include <iostream>

int main() {
    int valor = 42;
    int& alias = valor;  // 'alias' NO es una variable nueva

    std::cout << "valor = " << valor << " en la direccion " << &valor << '\n';
    std::cout << "alias = " << alias << " en la direccion " << &alias << '\n';
    std::cout << "Misma direccion? " << ((&valor == &alias) ? "SI" : "NO") << "\n\n";

    alias = 7;  // escribir en el alias es escribir en valor
    std::cout << "despues de 'alias = 7':   valor = " << valor << '\n';

    valor = 100;  // y al reves
    std::cout << "despues de 'valor = 100': alias = " << alias << "\n\n";

    // El punto que mas confunde:
    int otro = 500;
    alias = otro;  // asigna el VALOR de otro a valor;
                   // alias SIGUE siendo alias de valor
    std::cout << "despues de 'alias = otro':\n";
    std::cout << "  valor = " << valor << " en " << &valor << '\n';
    std::cout << "  otro  = " << otro << " en " << &otro << '\n';
    std::cout << "  alias sigue ligado a valor: "
              << ((&alias == &valor) ? "SI" : "NO") << "\n\n";

    // int& sin_inicializar;      // error: requiere un inicializador
    // int& a_un_numero = 5;      // error: no se puede ligar a un literal

    std::cout << "CONCLUSION: una referencia se liga a una variable al nacer\n"
              << "y ya no se puede reapuntar. Es un apodo, no una copia.\n";
    return 0;
}
