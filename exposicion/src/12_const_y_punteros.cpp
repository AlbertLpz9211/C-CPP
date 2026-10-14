// ===========================================================================
// 12 - Donde va el const
// Bloque 5 (20 min) - const, punteros vs referencias
//
// OBJETIVO
//   Aclarar de una vez las cuatro combinaciones de const con punteros, porque
//   aparecen constantemente en las firmas de funciones que reciben arreglos.
//
//   REGLA DE LECTURA: se lee de DERECHA A IZQUIERDA a partir del identificador.
//
//     int* p;              p: puntero a int                (todo modificable)
//     const int* p;        p: puntero a int constante      (no se puede *p = ...)
//     int* const p;        p: puntero constante a int      (no se puede p = ...)
//     const int* const p;  p: puntero constante a int constante
//
//   'const int*' y 'int const*' son el mismo tipo. La segunda forma hace la
//   regla de derecha a izquierda mas evidente, pero la primera es la habitual.
//
//   Con referencias no hay ambiguedad: la referencia nunca se reapunta, asi
//   que solo existe 'const T&' (leer) y 'T&' (leer y escribir).
// ===========================================================================

#include <iostream>

int main() {
    int a = 1;
    int b = 2;

    // 1) puntero normal: se puede cambiar el destino y el valor apuntado
    int* p1 = &a;
    *p1 = 10;
    p1 = &b;
    std::cout << "1) int* p            : *p y p modificables. a=" << a << " b=" << b << '\n';

    // 2) puntero a const: NO se puede escribir a traves de el, pero si reapuntar
    const int* p2 = &a;
    // *p2 = 20;   // error: read-only variable is not assignable
    p2 = &b;       // permitido
    std::cout << "2) const int* p      : lectura solamente; se puede reapuntar. *p2=" << *p2 << '\n';

    // 3) puntero constante: se puede escribir el valor, pero no reapuntar
    int* const p3 = &a;
    *p3 = 30;
    // p3 = &b;    // error: cannot assign to variable 'p3' with const-qualified type
    std::cout << "3) int* const p      : escribe el valor, no se reapunta. a=" << a << '\n';

    // 4) todo constante
    const int* const p4 = &a;
    // *p4 = 40;   // error
    // p4 = &b;    // error
    std::cout << "4) const int* const p: nada modificable. *p4=" << *p4 << "\n\n";

    // --- Aplicacion a parametros de funcion ---------------------------------
    std::cout << "EN PARAMETROS DE FUNCION\n"
              << "  void imprime(const int* datos, std::size_t n);\n"
              << "      -> la funcion promete NO modificar el arreglo del llamador.\n"
              << "  void llena  (int* datos, std::size_t n);\n"
              << "      -> la funcion SI va a escribir en el arreglo del llamador.\n\n"
              << "  Poner const donde corresponde no es cosmetica: es la unica\n"
              << "  documentacion que el compilador verifica.\n";
    return 0;
}
