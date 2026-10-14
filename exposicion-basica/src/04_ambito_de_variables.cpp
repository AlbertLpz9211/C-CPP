// ===========================================================================
// 04 - Ambito de las variables: lo que nace dentro, muere dentro
// Bloque 1 (30 min) - Funciones
//
// OBJETIVO
//   Ver que cada funcion tiene sus propias variables, aunque se llamen igual,
//   y que dejan de existir al terminar la funcion.
//
// REGLA
//   Una variable declarada dentro de una funcion (o de un bloque) existe solo
//   desde su declaracion hasta la llave de cierre.
//
// PARA LA EXPOSICION
//   Descomentar la ultima linea de main para mostrar el error del compilador.
// ===========================================================================

#include <iostream>

void primera() {
    int contador = 100;  // esta 'contador' pertenece a primera()
    std::cout << "  primera(): contador = " << contador
              << " en la direccion " << &contador << '\n';
}

void segunda() {
    int contador = 999;  // otra variable distinta, con el mismo nombre
    std::cout << "  segunda(): contador = " << contador
              << " en la direccion " << &contador << '\n';
}

void cuenta_desde_cero() {
    int visitas = 0;  // se crea de nuevo en CADA llamada
    ++visitas;
    std::cout << "  visitas = " << visitas << '\n';
}

int main() {
    int contador = 1;  // la 'contador' de main
    std::cout << "main    : contador = " << contador
              << " en la direccion " << &contador << "\n\n";

    primera();
    segunda();

    std::cout << "\nmain    : contador sigue valiendo " << contador << "\n\n";

    std::cout << "Tres llamadas seguidas a cuenta_desde_cero():\n";
    cuenta_desde_cero();
    cuenta_desde_cero();
    cuenta_desde_cero();

    std::cout << "\nUn bloque tambien crea ambito:\n";
    {
        int solo_aqui = 5;
        std::cout << "  dentro del bloque: solo_aqui = " << solo_aqui << '\n';
    }
    // std::cout << solo_aqui;   // error: use of undeclared identifier

    std::cout << "\nCONCLUSION: cada funcion trabaja en su propio espacio.\n"
              << "Por eso una funcion no puede tocar las variables de otra...\n"
              << "salvo que se las pasemos. De eso trata el resto de la sesion.\n";
    return 0;
}
