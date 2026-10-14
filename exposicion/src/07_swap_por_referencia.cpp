// ===========================================================================
// 07 - El intercambio que si funciona
// Bloque 4 (35 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Cerrar el problema abierto en 03_swap_roto.cpp. El cuerpo de la funcion es
//   identico; lo unico que cambia son dos simbolos '&' en la lista de
//   parametros. Ese detalle cambia por completo el significado del programa.
//
// COMPARACION
//   void intercambia_mal(int  a, int  b);   // trabaja sobre copias
//   void intercambia    (int& a, int& b);   // trabaja sobre los originales
//
// EN C SE HACE CON PUNTEROS
//   void intercambia_c(int* a, int* b);  y se llama intercambia_c(&x, &y);
//   La version con referencias es la misma idea con mejor sintaxis y sin
//   posibilidad de recibir un puntero nulo.
// ===========================================================================

#include <iostream>
#include <utility>  // std::swap

// Version con referencias: los parametros son alias de los argumentos.
void intercambia(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// Version en estilo C, con punteros. Util para comparar.
void intercambia_con_punteros(int* a, int* b) {
    if (a == nullptr || b == nullptr) {  // con punteros hay que validar
        return;
    }
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

int main() {
    int x = 1;
    int y = 2;

    std::cout << "Con referencias\n"
              << "  antes   : x=" << x << " y=" << y << '\n';
    intercambia(x, y);  // se llama igual que la version por valor
    std::cout << "  despues : x=" << x << " y=" << y << "  <-- intercambiados\n\n";

    std::cout << "Con punteros (estilo C)\n"
              << "  antes   : x=" << x << " y=" << y << '\n';
    intercambia_con_punteros(&x, &y);  // hay que tomar la direccion explicitamente
    std::cout << "  despues : x=" << x << " y=" << y << "\n\n";

    std::cout << "Con la version de la biblioteca estandar\n"
              << "  antes   : x=" << x << " y=" << y << '\n';
    std::swap(x, y);  // <utility>; funciona con cualquier tipo movible
    std::cout << "  despues : x=" << x << " y=" << y << "\n\n";

    std::cout << "OBSERVACION IMPORTANTE\n"
              << "  En el punto de llamada, intercambia(x, y) se ve EXACTAMENTE igual\n"
              << "  que intercambia_mal(x, y). Solo la declaracion de la funcion dice\n"
              << "  si los argumentos pueden cambiar. Por eso hay que leer las firmas.\n";
    return 0;
}
