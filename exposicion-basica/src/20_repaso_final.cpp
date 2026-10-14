// ===========================================================================
// 20 - Repaso: las tres formas de pasar un argumento, en un solo programa
// Bloque 11 (5 min) - Cierre
//
// OBJETIVO
//   Reunir en un archivo corto todo lo visto, para leerlo de un vistazo.
//
// REGLA
//   int  n          -> copia.      La funcion no puede cambiar mi variable.
//   int& n          -> alias.      La funcion cambia mi variable.
//   const int& n    -> alias solo de lectura.
//   int v[], int n  -> direccion.  El arreglo no se copia nunca.
//
// PARA LA EXPOSICION
//   Cerrar la sesion recorriendo las cuatro firmas y su efecto.
// ===========================================================================

#include <iostream>

void por_valor(int n) {
    n = 100;
    std::cout << "  [dentro de por_valor] mi copia vale " << n << '\n';
}

void por_referencia(int& n) {
    n = 100;
}

void solo_lectura(const int& n) {
    std::cout << "  leo " << n << " sin poder cambiarlo\n";
}

void un_arreglo(int v[], int cuantos) {
    for (int i = 0; i < cuantos; ++i) {
        v[i] = 100;
    }
}

int main() {
    int a = 1;
    por_valor(a);
    std::cout << "despues de por_valor(a)      : a = " << a << "  (sin cambios)\n";

    int b = 1;
    por_referencia(b);
    std::cout << "despues de por_referencia(b) : b = " << b << "  (cambio)\n";

    int c = 7;
    solo_lectura(c);

    int v[3] = {1, 2, 3};
    un_arreglo(v, 3);
    std::cout << "despues de un_arreglo(v, 3)  : v = ";
    for (int i = 0; i < 3; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << " (cambio: los arreglos viajan por direccion)\n";

    std::cout << "\nLa pregunta de toda la sesion:\n"
              << "  que le llega realmente a la funcion?\n"
              << "  una copia, un alias, o una direccion.\n";
    return 0;
}
