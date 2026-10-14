// ===========================================================================
// 13 - Punteros: la tercera forma de pasar un argumento
// Bloque 6 (20 min) - Punteros basicos
//
// OBJETIVO
//   Presentar el puntero como "una variable que guarda una direccion" y ver
//   que pasar la direccion permite modificar el original, igual que con una
//   referencia pero con sintaxis explicita.
//
// REGLA
//   &x  da la direccion de x.      int* p = &x;   guarda esa direccion.
//   *p  es la variable apuntada.   *p = 5;        escribe en x.
//
// PARA LA EXPOSICION
//   Es el estilo del lenguaje C. Conviene reconocerlo, aunque en C++ se
//   prefiera la referencia.
// ===========================================================================

#include <iostream>

void intercambia_con_punteros(int* a, int* b) {
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

void intercambia_con_referencias(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// Un puntero TAMBIEN viaja por valor: la funcion recibe una copia de la
// direccion. Por eso *p = 10 si afecta al llamador, pero p = nullptr no.
void demuestra(int* p) {
    *p = 10;        // SI afecta a la variable del llamador
    p = nullptr;    // NO afecta al puntero del llamador
}

int main() {
    int x = 5;
    int* p = &x;  // p guarda la direccion de x

    std::cout << "x  = " << x << '\n';
    std::cout << "&x = " << &x << '\n';
    std::cout << "p  = " << p << "  (la misma direccion)\n";
    std::cout << "*p = " << *p << "  (el valor apuntado)\n\n";

    *p = 99;
    std::cout << "despues de '*p = 99':  x = " << x << "\n\n";

    int a = 1;
    int b = 2;

    intercambia_con_punteros(&a, &b);  // hay que escribir & en la llamada
    std::cout << "con punteros    : a = " << a << ", b = " << b << '\n';

    intercambia_con_referencias(a, b);  // la llamada se ve como por valor
    std::cout << "con referencias : a = " << a << ", b = " << b << "\n\n";

    int valor = 0;
    int* puntero;
    std::cout <<"valor del puntero " << puntero << "  <-- no inicializado\n";
    if(puntero != nullptr) {
        std::cout << "el puntero es nulo\n";
    } else {
        std::cout << "el puntero NO es nulo\n";
    }
    puntero = nullptr;  // inicializo el puntero a nulo
    std::cout << "valor del puntero " << puntero << "  <-- inicializado a nulo\n";
    if(puntero == nullptr) {
        std::cout << "el puntero es nulo\n";
    } else {
        std::cout << "el puntero NO es nulo\n";
    }
    puntero = &valor;
    demuestra(puntero);
    std::cout << "valor   = " << valor << "  <-- si cambio\n";
    puntero = nullptr;  // ahora si lo pongo nulo
    std::cout << "puntero = " << puntero << "  <-- NO se volvio nulo\n\n";

    std::cout << "CONCLUSION: referencia y puntero llevan a la funcion la\n"
              << "direccion del dato. La referencia es mas simple y no puede\n"
              << "ser nula; el puntero permite representar 'no hay dato'.\n";
    return 0;
}
