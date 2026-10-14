// ===========================================================================
// 06 - La referencia es un alias
// Bloque 4 (35 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Antes de pasar argumentos por referencia hay que entender que es una
//   referencia: OTRO NOMBRE para un objeto que ya existe. No es un objeto
//   nuevo, no es un puntero, no se puede reasignar.
//
// LAS TRES REGLAS DE UNA REFERENCIA (T&)
//   1. Debe inicializarse al declararse. No existe una referencia "vacia".
//   2. Queda ligada a ese objeto para siempre: no se puede reapuntar.
//   3. No puede ser nula: siempre hay un objeto detras.
//
// COMPROBACION CLAVE
//   &referencia == &objeto. La misma direccion => es el mismo objeto.
// ===========================================================================

#include <iostream>

void modifica(int& referencia) {
    std::cout << "  [dentro]  recibi el objeto que vive en " << &referencia << '\n';
    referencia = 999;  // Escribe en el objeto del llamador, no en una copia.
}

int main() {
    int valor = 42;
    int& alias = valor;  // 'alias' no es un objeto nuevo: es otro nombre de 'valor'

    std::cout << "Un alias local\n"
              << "  valor = " << valor << " en " << &valor << '\n'
              << "  alias = " << alias << " en " << &alias << '\n'
              << "  Misma direccion => mismo objeto: " << (&valor == &alias ? "SI" : "NO") << "\n\n";

    alias = 7;
    std::cout << "  Tras 'alias = 7', valor = " << valor << " (cambio el mismo objeto)\n\n";

    // La referencia NO se puede reapuntar. Esta linea no reapunta nada:
    int otro = 100;
    alias = otro;  // asigna el VALOR de 'otro' a 'valor'; alias sigue siendo alias de valor
    std::cout << "  Tras 'alias = otro': valor = " << valor << ", otro = " << otro
              << ", &alias = " << &alias << " (sigue apuntando a valor)\n\n";

    // Lo que NO compila (descomentar en clase para ver el error del compilador):
    //   int& sin_inicializar;      // error: declaration of reference variable requires
    //                              //        an initializer
    //   int& nula = nullptr;       // error: non-const lvalue reference cannot bind to
    //                              //        a value of unrelated type

    valor = 42;
    std::cout << "Paso por referencia a una funcion\n"
              << "  [antes]   valor = " << valor << " en " << &valor << '\n';
    modifica(valor);
    std::cout << "  [despues] valor = " << valor << "  <-- SI cambio\n\n"
              << "CONCLUSION: el parametro int& NO copia el argumento; se convierte en\n"
              << "otro nombre del mismo objeto. Por eso puede modificarlo.\n";
    return 0;
}
